/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ConnectionTCP
*/

#ifndef CONNECTIONTCP_HPP_
#define CONNECTIONTCP_HPP_

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "network/ISocket.hpp"

namespace babel::network {

    class TCPSocket:  public boost::enable_shared_from_this<TCPSocket>, public ISocket {
    public:
        TCPSocket() = delete;
        ~TCPSocket() = default;

        TCPSocket(const TCPSocket &) = delete;
        TCPSocket &operator=(const TCPSocket &) = delete;

        static boost::shared_ptr<TCPSocket> create(boost::asio::io_context &ioContext);
        boost::asio::ip::tcp::socket &socket();

        void write(const std::string &toAdd) override;
        void write(const std::string &toAdd, int size) override;
        void setWriteFct(const std::function<void ()> &handler) override;

        void setReadFct(const std::function<int(const std::string &data)> &handler) override;
        void read() override;

        void setDisconnectFct(const std::function<void()> &handler) override;

        bool isConnected() const override;

        std::array<unsigned char, 4> getIp() const override;

    private:
        TCPSocket(boost::asio::io_context &ioContext);

        void handleDisconnect();

        void readHandler(const boost::system::error_code &error, size_t size);

    private:

        std::function<void ()> _disconnectFct = nullptr;
        std::function<int(const std::string &data)> _readFct = nullptr;
        std::function<void()> _writeFct = nullptr;

        boost::asio::ip::tcp::socket _socket;

        bool _connected = true;

        char _bufferRead[10000];
        std::string _savedBuffer;


    };

}

#endif /* !CONNECTIONTCP_HPP_ */
