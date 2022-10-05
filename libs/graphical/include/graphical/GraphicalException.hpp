/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#ifndef GRAPHICALEXCEPTION_HPP
#define GRAPHICALEXCEPTION_HPP

#include <exception>
#include <string>

namespace babel::graphical
{
    class GraphicalException : public std::exception {
        public:
            GraphicalException(std::string component, std::string message);
            ~GraphicalException() override = default;
            GraphicalException(const GraphicalException &) = default;
            GraphicalException &operator=(const GraphicalException &) = default;

            [[nodiscard]] const char *what() const noexcept override;
            [[nodiscard]] const std::string &getComponent() const;

        private:
            std::string _component;
            std::string _message;
    };
}

#endif //GRAPHICALEXCEPTION_HPP
