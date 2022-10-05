/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** QTSocketUDP
*/

#include "network/QTSocketUDP.hpp"

using namespace babel::network;

QTSocketUDP::QTSocketUDP(short port, QObject *parent) : QObject(parent), _port(port)
{
    _socket = new QUdpSocket(this);
    bool result = _socket->bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress);
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    if (!result)
        throw QTSocketException("Unable to bind port");
}

QTSocketUDP::~QTSocketUDP()
{
}

void QTSocketUDP::write(const std::string &data)
{
}

void QTSocketUDP::write(const std::string &data, int size)
{
    _socket->writeDatagram(data.data(), size, QHostAddress(_hostReceiver.c_str()), _portReceiver);
}

void QTSocketUDP::read()
{
}

void QTSocketUDP::setReceiverInfo(const std::string &host, unsigned short port)
{
    _hostReceiver = host;
    _portReceiver = port;
}

void QTSocketUDP::setReadFct(const std::function<int(const std::string &)> &fct)
{
    _readFct = fct;
}

bool QTSocketUDP::isConnected() const
{
    return (_socket->isOpen());
}

void QTSocketUDP::setWriteFct(const std::function<void ()> &handler)
{
}

void QTSocketUDP::setDisconnectFct(const std::function<void()> &handler)
{
}

void QTSocketUDP::connected() const
{
    qDebug() << "Socket UDP is connected";
}

void QTSocketUDP::disconnected() const
{
    qDebug() << "Socket UDP is disconnected";
}

void QTSocketUDP::readyRead()
{
    QByteArray buffer;
    QHostAddress sender;
    quint16 senderPort;

    buffer.resize(_socket->pendingDatagramSize());
    _socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);
    if (_readFct)
        _readFct(Utils::toStdString(buffer));
}

const std::string &QTSocketUDP::getHost() const noexcept
{
    return (_host);
}

int QTSocketUDP::getPort() const noexcept
{
    return (_port);
}

std::array<unsigned char, 4> QTSocketUDP::getIp() const
{
    std::array<unsigned char, 4> ip;
    ip[0] = 0;
    ip[1] = 0;
    ip[2] = 0;
    ip[3] = 0;
    return ip;
}
