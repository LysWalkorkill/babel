/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ISocket
*/

#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

#include <functional>
#include <string>
#include <array>

namespace babel::network {

    /// ISocket is an interface for a server socket.
    class ISocket {
    public:
        virtual ~ISocket() = default;

        virtual void setReadFct(const std::function<int(const std::string &data)> &handler) = 0;
        virtual void read() = 0;

        virtual void write(const std::string &toAdd) = 0;
        virtual void write(const std::string &toAdd, int size) = 0;
        virtual void setWriteFct(const std::function<void ()> &handler) = 0;

        virtual void setDisconnectFct(const std::function<void()> &handler) = 0;

        virtual bool isConnected() const = 0;

        virtual std::array<unsigned char, 4> getIp() const = 0;
    };

}

#endif /* !ISOCKET_HPP_ */
