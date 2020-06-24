#include<iostream>
#include<boost/asio.hpp>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

int main(int, char**) {
    try {
        std::cout << "Start client!" << std::endl;
        ba::io_service service;
        tcp::socket socket(service);
        socket.connect(tcp::endpoint(ba::ip::address::from_string("127.0.0.1"), 1500));
        std::string msg("ping");
        ba::write(socket, ba::buffer(msg + "!"));
        std::cout << "Sent msg!" << std::endl;
        ba::streambuf buf;
        ba::read_until(socket, buf, "!");
        std::cout << "Got msg (" << std::string(ba::buffer_cast<const char*>(buf.data())) << ")" << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop client!" << std::endl;
    return 0;
}
