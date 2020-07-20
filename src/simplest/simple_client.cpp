#include "tcp/io_socket.hpp"

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

constexpr int PORT = 1500;

static const std::string msg = [] () {
    const int n(100);
    std::string res;
    for (int i(0); i < n; ++i) {
        for (int j(0); j < n; ++j)
            res += std::to_string(i);
        res += '\n';
    }
    res.pop_back();
    return res;
}();

int main(int, char**) {
    try {
        std::cout << "Start client!" << std::endl;
        ba::io_service service;
        tcp::socket socket(service);
        socket.connect(tcp::endpoint(ba::ip::address::from_string("127.0.0.1"), PORT));
        // net::write(socket, "ping");
        net::write(socket, msg);
        net::read<true>(socket);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop client!" << std::endl;
    return 0;
}
