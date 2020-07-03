#include <system_error>
#include "async.hpp"

constexpr int PORT = 1504;

int main(int, char**) {
    std::cout << "Start async server!" << std::endl;
    try {
        boost::asio::io_context io_context;
        async::Server s(io_context, PORT);
        auto exec = [](boost::asio::io_context &io_context) {
            io_context.run();
        };
        // const auto proc_count = std::thread::hardware_concurrency();
        const auto proc_count(2);
        std::cout << "threads " << proc_count << std::endl;
        std::vector<std::thread> workers;;
        for (int i(0); i < proc_count; ++i)
            workers.emplace_back(exec, std::ref(io_context));
        for (auto &w : workers)
            w.join();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
