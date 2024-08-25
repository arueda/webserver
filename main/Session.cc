//  Copyright 2024 Angel Alberto Rueda Mejia

#include "Session.h"

#include <utility>

Session::Session(net::ip::tcp::socket socket): _socket(std::move(socket)) {}

void Session::run() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    http::async_read(_socket,
                     _buffer,
                     _req,
                     [this, self](beast::error_code ec, std::size_t) {
        if (!ec) {
            http::response<http::string_body> response = handle_request(_req);
            do_write(response);
        }
    });
}

void Session::do_write(http::response<http::string_body> response) {
    auto self(shared_from_this());
    auto sp = std::make_shared<http::response<http::string_body>>(std::move(response));
    http::async_write(_socket, *sp, [this, self, sp](beast::error_code ec, std::size_t) {
        _socket.shutdown(net::ip::tcp::socket::shutdown_send, ec);
    });
}

http::response<http::string_body> Session::handle_request(http::request<beast::http::string_body> const& req) {
    // Respond to GET request with "Hello, World!"
    if (req.method() == http::verb::get) {
        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Beast");
        res.set(http::field::content_type, "text/plain");
        res.keep_alive(req.keep_alive());
        res.body() = "Hello, World!";
        res.prepare_payload();
        return res;
    }

    // Default response for unsupported methods
    return http::response<http::string_body>{http::status::bad_request, req.version()};
}

