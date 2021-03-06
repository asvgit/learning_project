#include <system_error>
#include "tcp/io_socket.hpp"
#include "fs/io_file.hpp"
#include <thread>
#include <queue>

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

constexpr int PORT = 1502;

using Workers = std::vector<std::thread>;
using Queue = std::queue<tcp::socket>;
static struct {
    std::atomic_bool shut{false};
    std::mutex m;
    std::condition_variable cv;
    Queue q;
} sync_data{};

void fill_poll(Workers &poll) {
    const auto hc = std::thread::hardware_concurrency();
    const auto poll_size = hc / 2 > 0 ? hc / 2 : 1;
    auto exec = [] (int id) {
        while (true) {
            std::unique_lock<std::mutex> lk(sync_data.m);
            while (sync_data.q.empty() && !sync_data.shut.load()) {
                sync_data.cv.wait(lk);
            }
            if (sync_data.q.empty() && sync_data.shut.load())
                return;
            auto socket = std::move(sync_data.q.front());
            sync_data.q.pop();
            lk.unlock();
            const auto resp = net::read(socket);
            if (resp == SHUTDOWN_CMD) {
                net::write(socket, "ok");
                sync_data.shut.store(true);
            } else if (resp == PING_CMD) {
                net::write(socket, "pong");
            } else {
                net::write(socket, resp);
                for (int i(10); i; --i) {
                    fs::write(resp, std::string("mt_") + std::to_string(id) + std::string("_") + DEF_FILE);
                    auto file_data = fs::read();
                }
            }
        }
    };
    for (int i(0); i < poll_size; ++i)
        poll.emplace_back(exec, i);
}

void run() {
    ba::io_service service;
    tcp::acceptor acceptor(service, tcp::endpoint(tcp::v4(), PORT));
    while (!sync_data.shut.load()) {
        tcp::socket socket(service);
        //TODO: add timeout for shutdown
        acceptor.accept(socket);
        // std::cout << "Socket accepted!" << std::endl;
        std::unique_lock<std::mutex> lk(sync_data.m);
        sync_data.q.emplace(std::move(socket));
        sync_data.cv.notify_one();
    }
}

int main(int, char**) {
    try {
        std::cout << "Start server!" << std::endl;
        Workers poll;
        fill_poll(poll);
        run();
        sync_data.cv.notify_all();
        std::cout << "Join workers!" << std::endl;
        for (auto &i: poll)
            i.join();
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "Something got wrong!" << std::endl;
    }
    std::cout << "Stop server!" << std::endl;
    return 0;
}
