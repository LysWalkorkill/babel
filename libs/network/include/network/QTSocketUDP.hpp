/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** QTSocketUDP
*/

#ifndef QTSOCKETUDP_HPP_
#define QTSOCKETUDP_HPP_

#include <QNetworkAddressEntry>
#include <QObject>
#include <QDebug>
#include <QUdpSocket>
#include <QAbstractSocket>
#include "ISocket.hpp"
#include "Exception.hpp"
#include "Utils.hpp"

namespace babel::network
{
    class QTSocketUDP : public QObject, public ISocket {
        Q_OBJECT

        public:
            QTSocketUDP() = delete;
            QTSocketUDP(short port, QObject *parent = 0);
            ~QTSocketUDP();
            QTSocketUDP(const QTSocketUDP &) = delete;
            QTSocketUDP &operator=(const QTSocketUDP &) = delete;

            void write(const std::string &data) override;
            void write(const std::string &data, int size) override;
            void read() override;
            void setReadFct(const std::function<int(const std::string &)> &fct) override;
            bool isConnected() const override;
            void setWriteFct(const std::function<void ()> &handler) override;
            void setDisconnectFct(const std::function<void()> &handler) override;
            void setReceiverInfo(const std::string &host, unsigned short port);

            const std::string &getHost() const noexcept;
            int getPort() const noexcept;

        private:

            std::array<unsigned char, 4> getIp() const override;

        public slots:
            void connected() const;
            void disconnected() const;
            void readyRead();

        private:
            QUdpSocket *_socket = nullptr;
            QByteArray _readData;
            QByteArray _writeData;
            std::string _host;
            unsigned short _port;
            std::string _hostReceiver;
            unsigned short _portReceiver;
            std::function<int(const std::string &)> _readFct = nullptr;
    };
} // namespace babel::network



#endif /* !QTSOCKETUDP_HPP_ */
