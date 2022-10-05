/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#ifndef CLIENTEXCEPTION_HPP
#define CLIENTEXCEPTION_HPP

#include <exception>
#include <string>

namespace babel::client
{
    class ClientException : public std::exception {
        public:
            ClientException(std::string component, std::string message);
            ~ClientException() override = default;
            ClientException(const ClientException &) = default;
            ClientException &operator=(const ClientException &) = default;

            [[nodiscard]] const char *what() const noexcept override;
            [[nodiscard]] const std::string &getComponent() const;

        private:
            std::string _component;
            std::string _message;
    };

    class AudioException : public ClientException {
        public:
            explicit AudioException(const std::string &message);
            ~AudioException() override = default;
    };
}

#endif //BABEL_SERVER_CLIENTEXCEPTION_HPP
