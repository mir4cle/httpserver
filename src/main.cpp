#include <unistd.h>
#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <functional>
#include <thread>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>

#include "http_server.h"

using namespace asio::ip;

int main(int argc, char **argv)
{
    address_v4 addr = make_address_v4("127.0.0.1");
    unsigned short port = 1234;
    std::string directory;

    // parse command line options
    char opt;
    while((opt = getopt(argc, argv, "h:p:d:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                addr = make_address_v4(optarg);
                break;

            case 'p':
                port = atoi(optarg);
                break;

            case 'd':
                directory = optarg;
                if(!directory.empty())
                {
                    char buf[PATH_MAX];
                    realpath(directory.c_str(), buf);
                    directory = buf;
                }
                break;

            default: break;
        }
    }
	
	// daemon
	signal(SIGHUP, SIG_IGN);
	daemon(0, 0);

    try
    {
        asio::io_service service;
        http_server server(service, addr, port, directory);

        unsigned int nThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        for (unsigned int i = 0; i < nThreads; ++i)
            threads.emplace_back([&service](){ service.run(); });

        for(auto &thread : threads)
            thread.join();
    }
    catch(std::exception &ex)
    {
        std::string error = ex.what();
        std::cerr << error << std::endl;
    }

    return 0;
}