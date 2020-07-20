#include "tcp/io_socket.hpp"

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

namespace {

std::string buf2string(boost::asio::streambuf &buf) {
    return {boost::asio::buffers_begin(buf.data()),
                boost::asio::buffers_begin(buf.data()) + buf.size()};
}

std::tuple<std::size_t, std::string> read_header(tcp::socket &socket) {
    int size(0);
    std::string data;
    while (size == 0) {
        ba::streambuf buf(1024);
        ba::read_until(socket, buf, '\n');
        data += buf2string(buf);
        auto it = data.find('\n');
        if (it != std::string::npos) {
            size = std::stoi(data.substr(0, it));
            data = data.substr(it + 1);
        }
    }
    return {size, data};
}

std::string read_body(tcp::socket &socket, std::size_t size, const std::string &prev_data = "") {
    std::string resp, data(prev_data);
    while (size > 0) {
        auto it = data.find('\n');
        for (; it != std::string::npos; it = data.find('\n')) {
            resp += data.substr(0, it + 1);
            data = data.substr(it + 1);
            --size;
        }
        if (size <= 0)
            break;
        ba::streambuf buf(1024);
        ba::read_until(socket, buf, '\n');
        data += buf2string(buf);
    }
    resp.pop_back();
    return resp;
}

} // end of private namespace

namespace net {

template<>
std::string read<false>(tcp::socket &socket) {
    int size;
    std::string data;
    std::tie(size, data) = read_header(socket);
    return read_body(socket, size, data);
}

template<>
std::string read<true>(tcp::socket &socket) {
    std::cout << "Start read" << std::endl;
    int size;
    std::string data;
    std::tie(size, data) = read_header(socket);
    std::cout << "Got size (" << size << ")" << std::endl;
    auto resp = read_body(socket, size, data);
    std::cout << "Got msg with size (" << resp.size() << ")" << std::endl;
    return resp;
}

}