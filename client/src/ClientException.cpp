/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#include "ClientException.hpp"
#include <utility>

using namespace babel::client;

ClientException::ClientException(std::string component, std::string message) : _component(std::move(component)), _message(std::move(message))
{
}

const char *ClientException::what() const noexcept
{
    return (_message.c_str());
}

const std::string &ClientException::getComponent() const
{
    return (_component);
}

AudioException::AudioException(const std::string &message) : ClientException("Audio", message)
{
}
