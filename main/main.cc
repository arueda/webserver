#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace net = boost::asio;

class Listener: public std::enable_shared_from_this<Listener> {
    net::io_context& ioc_;
    net::ip::tcp::acceptor acceptor_;
  
    public: 
    Listener(
        net::io_context& ioc,
        net::ip::tcp::endpoint endpoint
    ) : ioc_(ioc), acceptor_(net::make_strand(ioc)) {
        beast::error_code ec;
        acceptor_.open(endpoint.protocol(), ec);
        if (ec) {
            std::cerr << "Open error" << ec.message() << std::endl;
            return;
        }

        acceptor_.set_option(net::socket_base::reuse_address(true), ec);
    }
    
    static std::shared_ptr<Listener> create(
        net::io_context& ioc, 
        net::ip::tcp::endpoint endpoint
    ) {
        return std::make_shared<Listener>(ioc, endpoint);
    }

    std::shared_ptr<Listener> getptr() {
        return shared_from_this();
    }
};

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

