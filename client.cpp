#include"io_socket.hpp"

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

int main(int, char**) {
    try {
        std::cout << "Start client!" << std::endl;
        ba::io_service service;
        tcp::socket socket(service);
        socket.connect(tcp::endpoint(ba::ip::address::from_string("127.0.0.1"), 1500));
        write(socket, "ping");
        std::cout << "Client sent msg!" << std::endl;
        read(socket);
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop client!" << std::endl;
    return 0;
}
