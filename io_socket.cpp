#include"io_socket.hpp"
#include<iterator>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

namespace {

std::string buf2string(ba::streambuf &buf) {
    return {boost::asio::buffers_begin(buf.data()),
                boost::asio::buffers_begin(buf.data()) + buf.size()};
}

} // end of private namespace

std::string read(tcp::socket &socket) {
    std::cout << "Start read" << std::endl;
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
    std::cout << "Got size (" << size << ")" << std::endl;
    std::string resp;
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
    std::cout << "Got msg with size (" << resp.size() << ")" << std::endl;
    return resp;
}

void write(tcp::socket &socket, const std::string &msg) {
    const std::string data = msg + '\n';
    auto cmp = [](const char i) { return i == '\n'; };
    const auto size = std::count_if(data.begin(), data.end(), cmp);
    ba::write(socket, ba::buffer(std::to_string(size) + "\n"));
    ba::write(socket, ba::buffer(data));
    // std::cout << "Set data (" << data << ")" << std::endl;
}
