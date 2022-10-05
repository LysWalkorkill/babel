/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <exception>
#include <string>

namespace babel::network
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

    class QTSocketException : public Exception {
        public:
            explicit QTSocketException(const std::string &message);
            ~QTSocketException() override = default;
    };
} // namespace babel::network



#endif /* !EXCEPTION_HPP_ */
