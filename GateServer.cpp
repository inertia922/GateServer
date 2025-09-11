#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "CServer.h"

int main()
{
    try {
        uint16_t port = 8080;
        net::io_context ioc{ 1 }; //1个io线程

        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);

        signals.async_wait([&ioc](const boost::system::error_code& error, int signal_number) {
            if (error) {
                std::cerr << "exception message:" << error.message() << std::endl;
                return;
            }
            ioc.stop();
            
            }
        );

        std::make_shared<CServer>(ioc, port)->Start();
        std::cout << "Gate server listen on port: " << port << std::endl;
        ioc.run();

    }
    catch (std::exception &e) {
        std::cerr << "exception err:" << e.what() << std::endl;
    }
}