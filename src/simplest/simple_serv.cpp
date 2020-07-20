#include <system_error>
#include "tcp/io_socket.hpp"
#include "fs/io_file.hpp"

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

constexpr int PORT = 1501;

void run() {
    ba::io_service service;
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), PORT));
    while (true) {
        tcp::socket socket(service);
        acceptor.accept(socket);
        const auto resp = net::read(socket);
        if (resp == SHUTDOWN_CMD) {
            net::write(socket, "ok");
            break;
        } else if (resp == PING_CMD) {
            net::write(socket, "pong");
        } else {
            net::write(socket, resp);
            for (int i(10); i; --i) {
                fs::write(resp);
                auto file_data = fs::read();
            }
        }
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
