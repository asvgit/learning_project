#pragma once
#include "tcp/io_socket.hpp"

namespace async {

namespace ba = boost::asio;
using tcp = ba::ip::tcp;

class Server {
public:
    Server(ba::io_context &io_context, const int port = 1500);
private:
    tcp::acceptor acceptor;

    class Session : public std::enable_shared_from_this<Session> {
    public:
        Session(tcp::socket sock, int ind);
    private:
        tcp::socket socket;
        int id;
        std::string buf, data;
        std::size_t msg_size{0};
        int fs_counter{10};
        friend Server;

        void async_read_head();
        void handle(int size);
        void async_read_body();
        void async_write();
        void async_fs_write();
        void async_fs_read();
    };
    void do_accept();
};

} // end of async namespace