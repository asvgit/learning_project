#include <system_error>
#include "tcp/io_socket.hpp"

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

constexpr int PORT = 1501;

void run() {
    ba::io_service service;
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), PORT));
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
    }
}

int main(int, char**) {
    std::cout << "Start server!" << std::endl;
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
