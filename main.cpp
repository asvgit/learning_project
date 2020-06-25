#include"io_socket.hpp"
#include<system_error>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

void run() {
    std::cout << "Start server!" << std::endl;
    ba::io_service service;
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), 1500));
    while (true) {
        tcp::socket socket(service);
        acceptor.accept(socket);
        const auto resp = read(socket);
        if (resp == SHUTDOWN_CMD) {
            write(socket, "ok");
            break;
        } else if (resp == PING_CMD) {
            write(socket, "pong");
        } else
            write(socket, resp);
        std::cout << "Server sent msg!" << std::endl;
    }
}

int main(int, char**) {
    try {
        run();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
