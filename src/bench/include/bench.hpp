#pragma once
#include <benchmark/benchmark.h>
#include <boost/thread.hpp>
#include "tcp/io_socket.hpp"

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

namespace mt {

template<const int PORT>
void exec() {
    namespace ba = boost::asio;
    using tcp = ba::ip::tcp;
    ba::io_service service;
    for (int i(0); i < 10; ++i) {
        tcp::socket socket(service);
        socket.connect(tcp::endpoint(ba::ip::address::from_string("127.0.0.1"), PORT));
        // write(socket, "ping");
        write/*<true>*/(socket, msg);
        read/*<true>*/(socket);
    }
}

template<const int PORT>
void bench(benchmark::State& state) {
    const auto proc_count = std::thread::hardware_concurrency() / 2;
    std::vector<std::thread> workers;
    workers.reserve(proc_count);
    for (auto _ : state) {
        for (int i(0); i < proc_count; ++i)
            workers.emplace_back(exec<PORT>);
        for (auto &w : workers)
            w.join();
        workers.clear();
    }
}

} // end of mt namespace
