#ifndef LISTENER_H
#define LISTENER_H

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;

class Listener: public std::enable_shared_from_this<Listener> {
    net::io_context& ioc_;
    net::ip::tcp::acceptor acceptor_;
    
public:
    Listener(
         net::io_context& ioc,
         net::ip::tcp::endpoint endpoint
    );

    static std::shared_ptr<Listener> create(
        net::io_context& ioc,
        net::ip::tcp::endpoint endpoint
    );

    std::shared_ptr<Listener> getptr();
 
private:
    void do_accept();

};

#endif
