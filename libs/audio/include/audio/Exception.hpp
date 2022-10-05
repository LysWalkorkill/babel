/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <string>
#include <exception>

namespace babel::audio
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

    class AudioException : public Exception {
        public:
            explicit AudioException(const std::string &message);
            ~AudioException() override = default;
    };
} // namespace babel::audio


#endif /* !EXCEPTION_HPP_ */
