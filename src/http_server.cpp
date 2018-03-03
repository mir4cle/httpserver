#include "http_server.h"
#include <signal.h>

using namespace asio::ip;
using asio::ip::tcp;

http_server::http_server(asio::io_service &service, const address_v4 &addr, unsigned short port, const std::string &root)
        : acceptor_(service, tcp::endpoint(addr, port))
        , socket_(acceptor_.get_io_service())
        , request_handler_(root)
        , signals_(acceptor_.get_io_service())
{
    // register signals
    signals_.add(SIGINT);
    signals_.add(SIGTERM);

    await_stop();

    start_accept();
}

void http_server::start_accept()
{
    acceptor_.async_accept(socket_,
        [this](const asio::error_code& error)
        {
            if (!error)
                connection_manager_.start(std::make_shared<connection>(std::move(socket_), connection_manager_, request_handler_));

            start_accept();
        });
}

void http_server::await_stop()
{
  signals_.async_wait(
    [this](std::error_code /*ec*/, int /*signo*/)
    {
        acceptor_.close();
        connection_manager_.stop_all();
    });
}