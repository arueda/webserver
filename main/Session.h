#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

namespace beast = boost::beast;
namespace net = boost::asio;

class Session: public std::enable_shared_from_this<Session> {
    net::ip::tcp::socket _socket;

public:
    explicit Session(net::ip::tcp::socket socket);
    void run();
};


#endif
