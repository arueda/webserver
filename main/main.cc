#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

#include "Session.h"
#include "Listener.h"

namespace beast = boost::beast;
namespace net = boost::asio;

int main() {
    try {
        std::cout << "arueda webserver 0.0.1 - 2024" << std::endl;
        auto const address = net::ip::make_address("0.0.0.0");
        unsigned short port = 8080;
        net::io_context ioc{1};
        std::shared_ptr<Listener> listener = Listener::create(
            ioc,
            net::ip::tcp::endpoint{address, port}
        );
        ioc.run();
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

