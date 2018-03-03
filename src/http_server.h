#pragma once

#include "connection_manager.h"
#include "request_handler.h"
#include <asio.hpp>
#include <string>

class http_server
{
public:
    http_server(asio::io_service &service, const asio::ip::address_v4 &addr, unsigned short port, const std::string &root);

private:
    void start_accept();
    void await_stop();

private:
    asio::ip::tcp::acceptor acceptor_;
    connection_manager connection_manager_;
    asio::ip::tcp::socket socket_;
    request_handler request_handler_;

    asio::signal_set signals_;
};