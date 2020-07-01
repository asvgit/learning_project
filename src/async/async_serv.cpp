#include <system_error>
#include "tcp/io_socket.hpp"
#include <thread>
#include <queue>
#include <memory>
#include <utility>
#include <cstdlib>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

constexpr int PORT = 1500;
constexpr int BUF_SIZE = 1024;

class Server {
public:
    Server(ba::io_context &io_context)
        : acceptor(io_context, tcp::endpoint(tcp::v4(), PORT)) { do_accept(); }

private:
    tcp::acceptor acceptor;

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket sock)
            : socket(std::move(sock)), buf(BUF_SIZE, '\0') {}

    private:
        tcp::socket socket;
        std::string buf, data;
        std::size_t msg_size{0};
        friend Server;

        void async_read_head() {
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

        void handle(int size) {
            msg_size -= std::count(buf.cbegin(), buf.cbegin() + size, '\n');
            data += buf.substr(0, size);
            if (!msg_size) {
                // std::cout << "Got msg size (" << data.size() << ")" << std::endl;
                // std::cout << "Got msg (" << data << ")" << std::endl;
                async_write();
            } else
                async_read_body();
        }

        void async_read_body() {
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

        void async_write() {
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
    };

    void do_accept() {
        acceptor.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket)
        {
            if (!ec) {
                std::make_shared<Session>(std::move(socket))->async_read_head();
            }
            do_accept();
        });
    }
};

int main(int, char**) {
    std::cout << "Start async server!" << std::endl;
    try {
        ba::io_context io_context;
        Server s(io_context);
        io_context.run();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
