//  Copyright 2024 Angel Alberto Rueda Mejia

#include "Listener.h"

#include <iostream>

int main() {
    try {
        std::cout << "arueda webserver 0.0.1 - 2024" << std::endl;
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = 8080;
        net::io_context ioc{1};

        auto endpoint = net::ip::tcp::endpoint(address, port);
        auto listener = std::make_shared<Listener>(ioc, endpoint);

        ioc.run();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

