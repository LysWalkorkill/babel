/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** QTSocket
*/

#include "network/QTSocketTCP.hpp"
#include "network/Exception.hpp"
#include <iostream>

using namespace babel::network;

QTSocketTCP::QTSocketTCP(const std::string &host, int port, QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket(this);

    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    _host = host;
    _hostPort = port;
    _socket->connectToHost(host.c_str(), port);
}

QTSocketTCP::~QTSocketTCP()
{
    _socket->close();
}

void QTSocketTCP::write(const std::string &data)
{
    std::cout << "{CLIENT} writing " << data.size() << std::endl;
    _socket->write(data.c_str(), data.size());
}

void QTSocketTCP::write(const std::string &data, int size)
{
}

void QTSocketTCP::setReadFct(const std::function<int(const std::string &)> &fct)
{
    _readFct = fct;
}

void QTSocketTCP::read()
{
}

bool QTSocketTCP::isConnected() const
{
    return (_socket->state() == QAbstractSocket::SocketState::ConnectedState);
}

void QTSocketTCP::setWriteFct(const std::function<void ()> &)
{
}

void QTSocketTCP::setDisconnectFct(const std::function<void()> &)
{
}

void QTSocketTCP::connected() const
{
    qDebug() << "Client connected to server at" << _host.c_str() << ":" << _hostPort << "with port" << _socket->localPort();
}

void QTSocketTCP::disconnected() const
{
    qDebug() << "Client disconnected from" << _host.c_str() << ":" << _hostPort;
}

void QTSocketTCP::bytesWritten(qint64 bytes) const
{
    qDebug() << "Client wrote:" << bytes;
}

void QTSocketTCP::readyRead()
{
    qDebug() << "Reading data from server";
    _readData.append(_socket->readAll());
    std::cout << "Receive : " << _readData.size() << std::endl;
    // _readData.truncate(_readFct(_readData.toStdString()));
    while (_readData.size() != 0) {
        int size = _readFct(Utils::toStdString(_readData));
        if (size == 0)
            break;
        _readData.remove(0, size);
    }
    // std::copy_n(str.begin() + sizeof(Header), header.messageSize, message.begin());
}


std::array<unsigned char, 4> QTSocketTCP::getIp() const
{
    std::array<unsigned char, 4> ip;
    ip[0] = 0;
    ip[1] = 0;
    ip[2] = 0;
    ip[3] = 0;
    return ip;
}

void QTSocketTCP::connectHost() const
{
    _socket->connectToHost(_host.c_str(), _hostPort);
}
