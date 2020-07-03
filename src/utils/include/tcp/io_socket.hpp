#pragma once
#include <boost/asio.hpp>
#include <iostream>

constexpr int BUF_SIZE = 1024;
constexpr char SHUTDOWN_CMD[] = "shutdown_now";
constexpr char PING_CMD[] = "ping";

template<bool DEBUG = false>
std::string read(boost::asio::ip::tcp::socket &socket);

template<bool DEBUG = false>
void write(boost::asio::ip::tcp::socket &socket, const std::string &msg) {
    const std::string data = msg + '\n';
    auto cmp = [](const char i) { return i == '\n'; };
    const auto size = std::count_if(data.begin(), data.end(), cmp);
    boost::asio::write(socket, boost::asio::buffer(std::to_string(size) + "\n"));
    boost::asio::write(socket, boost::asio::buffer(data));
    if (DEBUG)
        std::cout << "Sent data size (" << data.size() << ")" << std::endl;
}