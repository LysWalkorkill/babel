/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ClientInfo
*/

#ifndef CLIENTINFO_HPP_
#define CLIENTINFO_HPP_

#include <optional>

#include "network/ISocket.hpp"
#include <boost/shared_ptr.hpp>
#include "server/Storage.hpp"

namespace babel::server
{

    struct ClientInfo {
    public:

        enum Status {
            FREE,
            INVITING,
            TRYING,
            RINGING,
            WAITING,
            WAITING_ACK,
            IN_CALL,
            CLOSING_CALL,
        };

    public:
        ClientInfo() = delete;

        ClientInfo(const ClientInfo &) = default;
        ClientInfo &operator=(const ClientInfo &) = default;
        ~ClientInfo() = default;

        ClientInfo(boost::shared_ptr<network::ISocket> &socket);

        boost::shared_ptr<network::ISocket> socket;
        std::optional<table::User> user;

        bool isReading = false;

        Status status = FREE;

        int otherUser = -1;
    };

} // namespace babel::server



#endif /* !CLIENTINFO_HPP_ */
