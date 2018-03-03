#pragma once

#include <memory>
#include <asio.hpp>

#include "request_parser.h"
#include "request.h"
#include "reply.h"

class connection_manager;
class request_handler;

class connection
    : public std::enable_shared_from_this<connection>
{
public:
    connection(const connection&) = delete;
    connection& operator=(const connection&) = delete;

    explicit connection(asio::ip::tcp::socket socket, connection_manager &manager, request_handler &handler);

    asio::ip::tcp::socket& socket();
    void start();
    void stop();

private:
    void read();
    void write();

private:
    asio::ip::tcp::socket socket_;
    connection_manager &connection_manager_;
    request_handler &request_handler_;
    request_parser request_parser_;
    request request_;
    reply reply_;
    std::string message_;
    std::array<char, 8192> buffer_;
};

typedef std::shared_ptr<connection> connection_ptr;