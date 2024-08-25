#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

#include "Session.h"

namespace beast = boost::beast;
namespace net = boost::asio;

Session::Session(net::ip::tcp::socket socket): _socket(std::move(socket)) {}

void Session::run() {}

