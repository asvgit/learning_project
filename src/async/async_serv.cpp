#include <system_error>
#include "async.hpp"

constexpr int PORT = 1503;

int main(int, char**) {
    std::cout << "Start async server!" << std::endl;
    try {
        boost::asio::io_context io_context;
        async::Server s(io_context, PORT);
        io_context.run();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
