#include <thread>
#include <functional>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "fs/io_file.hpp"
#include "iostream"

void io_operation(boost::asio::io_service &io_service, int parameter) {
    //Your stuff
    if (parameter == 0) {
        io_service.stop();
        return;
    }
    io_service.post(std::bind(io_operation, std::ref(io_service), parameter - 1));
    fs::write("test", std::string("async_") + DEF_FILE);
    std::cout << parameter << std::endl;
}

int main ( int argc, char* argv[] ) {
    boost::asio::io_service io_service;
    boost::asio::io_service::work work(io_service);

    //Set up a thread pool taking asynchronically care of your orders
    std::vector<std::thread> threadPool;

    for(size_t t = 0; t < std::thread::hardware_concurrency(); t++){
        threadPool.push_back(std::thread(boost::bind(&boost::asio::io_service::run, &io_service)));
    }

    //Post an IO-operation
    // io_service.post(std::bind(io_operation, 123));
    // io_service.post(std::bind(io_operation, std::ref(io_service), 10));
    int param{11};
    std::function<void(int)> async_impl;
    async_impl = [&async_impl, &io_service](int param) {
        if (param <= 0) {
            io_service.stop();
            return;
        }
        io_service.post(std::bind(async_impl, param - 1));
        fs::write("test", std::string("async_") + DEF_FILE);
        std::cout << param << std::endl;
    };
    io_service.post(std::bind(async_impl, param));

    //Join all threads at the end
    // io_service.stop();
    for(std::thread& t : threadPool) {
        t.join();
    }
}