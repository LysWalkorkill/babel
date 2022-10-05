/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ConnectionTCP
*/

#include "network/TCPSocket.hpp"
#include <iostream>
#include <boost/bind.hpp>

using namespace babel::network;

TCPSocket::TCPSocket(boost::asio::io_context &ioContext):
    _socket(ioContext)
{}

boost::shared_ptr<TCPSocket> TCPSocket::create(boost::asio::io_context &ioContext)
{
    return boost::shared_ptr<TCPSocket>(new TCPSocket(ioContext));
}

boost::asio::ip::tcp::socket &TCPSocket::socket()
{
    return _socket;
}

void TCPSocket::setReadFct(const std::function<int (const std::string &)> &handler)
{
    _readFct = handler;
}

void TCPSocket::read()
{
    if (_readFct == nullptr)
        return;

    boost::asio::async_read(
        _socket,
        boost::asio::buffer(_bufferRead, sizeof(_bufferRead)),
        boost::asio::transfer_at_least(1),
        boost::bind(
            &TCPSocket::readHandler,
            shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred
            )
        );
}

void TCPSocket::readHandler(const boost::system::error_code &error, size_t size)
{
    if (size == 0 || error) {
        return handleDisconnect();
    }
    std::cout << "size: " << size << std::endl;
    // ::write(1, _bufferRead, size);

    _savedBuffer.append(_bufferRead, size);
    while (_savedBuffer.size() != 0) {
        int toRemove = _readFct(_savedBuffer);

        if (toRemove == 0)
            break;

        _savedBuffer.erase(_savedBuffer.begin(), _savedBuffer.begin() + toRemove);
    }
}

void TCPSocket::setWriteFct(const std::function<void ()> &handler)
{
    _writeFct = handler;
}

void TCPSocket::write(const std::string &toWrite)
{
    boost::asio::async_write(
        _socket, boost::asio::buffer(toWrite),
        [this] (const boost::system::error_code &error, size_t size) -> void {
            if (error)
                return handleDisconnect();
            if (this->_writeFct != nullptr)
                this->_writeFct();
        });
}

void TCPSocket::write(const std::string &toWrite, int /* size */)
{
    this->write(toWrite);
}

bool TCPSocket::isConnected() const
{
    return _connected;
}

void TCPSocket::setDisconnectFct(const std::function<void ()> &fct)
{
    _disconnectFct = fct;
}

void TCPSocket::handleDisconnect()
{
    _connected = false;
    if (_disconnectFct)
        _disconnectFct();
}

std::array<unsigned char, 4> TCPSocket::getIp() const
{
    std::cout << _socket.remote_endpoint().address().to_v4() << std::endl;
    return _socket.remote_endpoint().address().to_v4().to_bytes();
}
