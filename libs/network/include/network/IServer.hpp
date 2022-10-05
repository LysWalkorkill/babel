/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

#include <functional>
#include "network/ISocket.hpp"
#include <boost/shared_ptr.hpp>

namespace babel::network {

    class IServer {
    public:
        virtual ~IServer() = default;

        virtual void setAcceptHandler(const std::function<bool(boost::shared_ptr<ISocket> &)> &fct) = 0;

        virtual void acceptClient() = 0;
        virtual void run() = 0;
    };

}

#endif /* !ISERVER_HPP_ */
