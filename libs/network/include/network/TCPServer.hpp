/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <boost/asio.hpp>
#include "network/TCPSocket.hpp"
#include "network/IServer.hpp"
#include <boost/bind.hpp>

namespace babel::network
{
    class TCPServer: public boost::enable_shared_from_this<TCPSocket>, public IServer {
    public:
        TCPServer(int port);
        ~TCPServer();
        TCPServer(const TCPServer &) = delete;
        TCPServer &operator=(const TCPServer &) = delete;

        void setAcceptHandler(const std::function<bool(boost::shared_ptr<ISocket> &)> &fct) override;

        void acceptClient() override;
        void run() override;

    private:
        boost::asio::io_context _context;
        boost::asio::ip::tcp::acceptor _acceptor;

        boost::shared_ptr<TCPSocket> _nextSocket;

        std::function<bool(boost::shared_ptr<ISocket> &)> _acceptHandler;
    };
} // namespace babel::server



#endif /* !SERVER_HPP_ */
