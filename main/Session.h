//  Copyright 2024 Angel Alberto Rueda Mejia

#ifndef MAIN_SESSION_H_
#define MAIN_SESSION_H_

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;

namespace http = beast::http;

class Session: public std::enable_shared_from_this<Session> {
    net::ip::tcp::socket _socket;
    beast::flat_buffer _buffer;
    beast::http::request<http::string_body> _req;

 public:
    explicit Session(net::ip::tcp::socket socket);
    void run();

 private:
    void do_read();
    void do_write(http::response<http::string_body> response);
    http::response<http::string_body> handle_request(http::request<http::string_body> const& req);
};

#endif  // MAIN_SESSION_H_
