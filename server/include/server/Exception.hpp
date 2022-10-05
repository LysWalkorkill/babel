/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#ifndef Exception_HPP_
#define Exception_HPP_

#include <exception>
#include <iostream>

namespace babel::server
{
    class Exception : public std::exception {
        public:
            Exception(const std::string &component, const std::string &message);
            ~Exception() override = default;
            Exception(const Exception &) = default;
            Exception &operator=(const Exception &) = default;

            [[nodiscard]] const char *what() const noexcept override;
            [[nodiscard]] const std::string &getComponent() const;

        private:
            std::string _component;
            std::string _message;
    };

    class DBHandlerException : public Exception {
        public:
            explicit DBHandlerException(const std::string &message);
            ~DBHandlerException() override = default;
    };

    class ServerException : public Exception {
        public:
            explicit ServerException(const std::string &message);
            ~ServerException() override = default;
    };
} // namespace babel::server

#endif /* !Exception_HPP_ */
