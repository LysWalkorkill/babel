/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ServerHandler
*/

#ifndef SERVERHANDLER_HPP_
#define SERVERHANDLER_HPP_

#include "server/ClientInfo.hpp"
#include "network/TCPServer.hpp"
#include "network/Protocol.hpp"
#include "DBHandler.hpp"
#include "UserHandler.hpp"

namespace babel::server {

    /// This class contains all handlers for TCP server, socket and db
    class ServerHandler {
    public:
        ServerHandler() = delete;
        ServerHandler(const ServerHandler &) = delete;
        ServerHandler &operator=(const ServerHandler &) = delete;

        ServerHandler(int port);
        ~ServerHandler() = default;

        void run();

    private:
        bool handleAccept(boost::shared_ptr<babel::network::ISocket> &connection);

        static std::string prepareHeader(unsigned short code, int size);
        void sendContactNotify(const User &user, bool status) const;

    private:
        void writeHandler(ClientInfo &clientInfo);
        int readHandler(ClientInfo &clientInfo, const std::string &str);
        void disconnectHandler(ClientInfo &clientInfo);
        void sendContacts() const;

    private:
        void byeEvt(ClientInfo &client, const std::string &message);
        void cancelEvt(ClientInfo &client, const std::string &message);
        void inviteEvt(ClientInfo &client, const std::string &message);
        void ackEvt(ClientInfo &client, const std::string &message);
        void registerEvt(ClientInfo &client, const std::string &message);
        void loginEvt(ClientInfo &client, const std::string &message);
        void logoutEvt(ClientInfo &client, const std::string &message);
        void contactsEvt(ClientInfo &client, const std::string &message);
        void infoEvt(ClientInfo &client, const std::string &message);

        void ringingEvt(ClientInfo &client, const std::string &message);
        void okEvt(ClientInfo &client, const std::string &message);

        void unknownEvt(ClientInfo &client, const std::string &message);

    private:
        boost::shared_ptr<ClientInfo> getClient(int userId) const;

    private:
        std::vector<boost::shared_ptr<ClientInfo>> _clients;
        network::TCPServer _server;
        DBHandler _dbHandler;
        UserHandler _userHandler;

        static const std::map<unsigned short, void (ServerHandler::*)(ClientInfo &client, const std::string &message)> eventsHandlers;
    };

}

#endif /* !SERVERHANDLER_HPP_ */
