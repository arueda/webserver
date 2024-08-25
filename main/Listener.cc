
#include <iostream>

#include "Session.h"
#include "Listener.h"

Listener::Listener(
    net::io_context& ioc,
    net::ip::tcp::endpoint endpoint
) : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
    beast::error_code ec;
    acceptor_.open(endpoint.protocol(), ec);
    if (ec) {
        std::cerr << "Open error: " << ec.message() << std::endl;
        return;
    }

    acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    if (ec) {
        std::cerr << "Set option error: " << ec.message() << std::endl;
        return;
    }
    
    acceptor_.bind(endpoint, ec);
    if (ec) {
        std::cerr << "Bind error: " << ec.message() << std::endl;
        return;
    }

    acceptor_.listen(net::socket_base::max_listen_connections, ec);
    if (ec) {
        std::cerr << "Listen error: " << ec.message() << std::endl;
        return;
    }

    do_accept();
}
    
std::shared_ptr<Listener> Listener::create(
        net::io_context& ioc,
        net::ip::tcp::endpoint endpoint
) {
    return std::make_shared<Listener>(ioc, endpoint);
}

std::shared_ptr<Listener> Listener::getptr() {
    return shared_from_this();
}

void Listener::do_accept() {
    acceptor_.async_accept(
        net::make_strand(ioc_),
        [this](beast::error_code ec, net::ip::tcp::socket socket) {
            if(!ec) {
                std::make_shared<Session>(std::move(socket))->run();
            }
            do_accept();
        }
    );
}

