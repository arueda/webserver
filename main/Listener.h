//  Copyright 2024 Angel Alberto Rueda Mejia

#ifndef MAIN_LISTENER_H_
#define MAIN_LISTENER_H_

#include <memory>

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
    Listener(net::io_context& ioc, net::ip::tcp::endpoint endpoint);
    std::shared_ptr<Listener> getptr();

 private:
    void do_accept();
};

#endif  // MAIN_LISTENER_H_
