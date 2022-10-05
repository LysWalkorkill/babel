/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Server
*/

#include "network/TCPServer.hpp"

using namespace babel::network;
using namespace boost::asio;

TCPServer::TCPServer(int port) :
    _context(),
    _acceptor(ip::tcp::acceptor(_context, ip::tcp::endpoint(ip::tcp::v4(), port)))
{}

TCPServer::~TCPServer()
{
}

void TCPServer::run()
{
    _context.run();
}
#include <iostream>
void TCPServer::acceptClient()
{
    _nextSocket = TCPSocket::create(_context);

    std::cout << "Ready to accept" << std::endl;
    _acceptor.async_accept(
        _nextSocket->socket(),
        [this] (const boost::system::error_code& error) {
            auto ptr = boost::static_pointer_cast<ISocket>(_nextSocket);

            if (_acceptHandler)
                if (!_acceptHandler(ptr))
                    return;
            acceptClient();
        });
}

void TCPServer::setAcceptHandler(const std::function<bool (boost::shared_ptr<ISocket> &)> &fct)
{
    _acceptHandler = fct;
}
