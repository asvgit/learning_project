#pragma once
#include<boost/asio.hpp>
#include<iostream>

constexpr char SHUTDOWN_CMD[] = "shutdown_now";
constexpr char PING_CMD[] = "ping";

std::string read(boost::asio::ip::tcp::socket &socket);
void write(boost::asio::ip::tcp::socket &socket, const std::string &msg);