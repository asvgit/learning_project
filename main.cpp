#include<iostream>
#include<boost/asio.hpp>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

int main(int, char**) {
    try {
        std::cout << "Start server!" << std::endl;
        ba::io_service service;
        tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 1500));
        tcp::socket socket(service);
        acceptor.accept(socket);
        ba::streambuf buf;
        ba::read_until(socket, buf, "!");
        std::cout << "Got msg (" << std::string(ba::buffer_cast<const char*>(buf.data())) << ")" << std::endl;
        std::string msg("pong");
        ba::write(socket, ba::buffer(msg + "!"));
        std::cout << "Sent msg!" << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
