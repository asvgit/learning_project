#include <benchmark/benchmark.h>
#include "io_socket.hpp"
#include <thread>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

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

template<const int PORT>
void exec() {
    ba::io_service service;
    for (int i(0); i < 10; ++i) {
        tcp::socket socket(service);
        socket.connect(tcp::endpoint(ba::ip::address::from_string("127.0.0.1"), PORT));
        // write(socket, "ping");
        write(socket, msg);
        read(socket);
    }
}

static void BM_MultithreadPing(benchmark::State& state) {
    const auto proc_count = std::thread::hardware_concurrency() / 2;
    for (auto _ : state) {
        std::vector<std::thread> workers;
        for (int i(0); i < proc_count; ++i)
            workers.emplace_back(exec<1501>);
        for (auto &w : workers)
            w.join();
    }
}
BENCHMARK(BM_MultithreadPing);

static void BM_MultithreadPing2(benchmark::State& state) {
    const auto proc_count = std::thread::hardware_concurrency() / 2;
    for (auto _ : state) {
        std::vector<std::thread> workers;
        for (int i(0); i < proc_count; ++i)
            workers.emplace_back(exec<1500>);
        for (auto &w : workers)
            w.join();
    }
}
BENCHMARK(BM_MultithreadPing2);

BENCHMARK_MAIN();