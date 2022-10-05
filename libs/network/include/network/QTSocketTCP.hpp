/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** QTSocket
*/

#ifndef QTSOCKETTCP_HPP_
#define QTSOCKETTCP_HPP_

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "ISocket.hpp"
#include "Utils.hpp"

#include <memory>

namespace babel::network
{
    class QTSocketTCP : public QObject, public ISocket {
        Q_OBJECT

        public:
            QTSocketTCP() = delete;
            QTSocketTCP(const std::string &host, int port, QObject *parent = 0);
            ~QTSocketTCP();
            QTSocketTCP(const QTSocketTCP &) = delete;
            QTSocketTCP &operator=(const QTSocketTCP &) = delete;

            void write(const std::string &data) override;
            void write(const std::string &data, int size) override;
            void read() override;
            void setReadFct(const std::function<int(const std::string &)> &fct) override;
            bool isConnected() const override;
            void setWriteFct(const std::function<void ()> &handler) override;
            void setDisconnectFct(const std::function<void()> &handler) override;
            void connectHost() const;

            std::array<unsigned char, 4> getIp() const override;

        signals:

        public slots:
            void connected() const;
            void disconnected() const;
            void bytesWritten(qint64 bytes) const;
            void readyRead();

        private:
            QTcpSocket *_socket = nullptr;
            QByteArray _readData;
            std::string _host;
            int _hostPort;
            std::function<int(const std::string &)> _readFct;
    };
} // namespace babel::network



#endif /* !QTSOCKET_HPP_ */
