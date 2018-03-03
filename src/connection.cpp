#include "connection.h"
#include "connection_manager.h"

#include "request_handler.h"

#include <sstream>

using namespace asio::ip;

connection::connection(tcp::socket socket, connection_manager &manager, request_handler &handler)
        : socket_(std::move(socket))
        , connection_manager_(manager)
        , request_handler_(handler)
{

}

tcp::socket& connection::socket()
{
    return socket_;
}

void connection::start()
{
    read();
}

void connection::stop()
{
    socket_.close();
}

void connection::read()
{
    socket_.async_read_some(asio::buffer(buffer_), 
        [this](const asio::error_code &ec, size_t bytes_transferred)
        {
            if(!ec)
            {
                std::stringstream ss(std::string(buffer_.data(), bytes_transferred));
                request_parser::result_type result = request_parser_.parse(request_, ss);

                if(result == request_parser::result_type::good)
                {
                    request_handler_.handle_request(request_, reply_);
                    write();
                }
                else if(result == request_parser::result_type::bad)
                {
                    reply_ = reply::stock_reply(reply::bad_request);
                    write();
                }
            }
            else if(ec != asio::error::operation_aborted)
            {
                connection_manager_.stop(shared_from_this());
            }
        });
}

void connection::write()
{
    socket_.async_write_some(reply_.to_buffers(),
        [this](asio::error_code ec, size_t bytes_transferred)
        {
            if(!ec)
            {
                asio::error_code ignored_ec;
                socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
            }

            if(ec != asio::error::operation_aborted)
            {
                connection_manager_.stop(shared_from_this());
            }
        });
}