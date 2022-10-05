/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#include "graphical/GraphicalException.hpp"

#include <utility>

using namespace babel::graphical;

GraphicalException::GraphicalException(std::string component, std::string message) : _component(std::move(component)), _message(std::move(message))
{
}

const char *GraphicalException::what() const noexcept
{
    return (_message.c_str());
}

const std::string &GraphicalException::getComponent() const
{
    return (_component);
}
