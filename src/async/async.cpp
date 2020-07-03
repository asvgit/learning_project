#include "async.hpp"

namespace async {


Server::Server(ba::io_context &io_context, const int port)
        : acceptor(io_context, tcp::endpoint(tcp::v4(), port)) { do_accept(); }

void Server::do_accept() {
    acceptor.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
    {
        if (!ec) {
            std::make_shared<Session>(std::move(socket))->async_read_head();
        }
        do_accept();
    });
}

Server::Session::Session(tcp::socket sock)
        : socket(std::move(sock)), buf(BUF_SIZE, '\0') {}

void Server::Session::async_read_head() {
    socket.async_read_some(boost::asio::buffer(buf),
        [this, self = shared_from_this()]
        (boost::system::error_code ec, std::size_t length)
    {
        if (ec) {
            std::cerr << ec.message() << std::endl;
            return;
        }
        data += buf.substr(0, length);
        auto it = data.find('\n');
        if (it != std::string::npos) {
            msg_size = std::stoi(data.substr(0, it));
            // std::cout << "Got size (" << msg_size << ")" << std::endl;
            buf = data.substr(it + 1) + std::string(it, '\0');
            // std::cout << "Got buf (" << buf << ")" << std::endl;
            data.clear();
            handle(buf.size() - it);
        } else {
            async_read_head();
        }
    });
}

void Server::Session::handle(int size) {
    msg_size -= std::count(buf.cbegin(), buf.cbegin() + size, '\n');
    data += buf.substr(0, size);
    if (!msg_size) {
        // std::cout << "Got msg size (" << data.size() << ")" << std::endl;
        // std::cout << "Got msg (" << data << ")" << std::endl;
        async_write();
    } else
        async_read_body();
}

void Server::Session::async_read_body() {
    auto self(shared_from_this());
    socket.async_read_some(boost::asio::buffer(buf),
        [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (ec) {
            std::cerr << ec.message() << std::endl;
            return;
        }
        handle(length);
    });
}

void Server::Session::async_write() {
    data.pop_back();
    const auto size = std::count(data.begin(), data.end(), '\n') + 1;
    const auto resp = data == PING_CMD
        ? "1\npong\n"
        : std::to_string(size) + "\n" + data + "\n";
    socket.async_write_some(ba::buffer(resp),
        [this, self = shared_from_this()]
        (boost::system::error_code ec, std::size_t)
    {
        if (ec)
            std::cerr << ec.message() << std::endl;
        // else
        //     std::cout << "Sent msg!" << std::endl;
    });
}

} // end of async namespace