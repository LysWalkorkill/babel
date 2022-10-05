/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#include "server/Exception.hpp"

using namespace babel::server;

Exception::Exception(const std::string &component, const std::string &message) : _component(component), _message(message)
{
}

const char *Exception::what() const noexcept
{
    return (_message.c_str());
}

const std::string &Exception::getComponent() const
{
    return (_component);
}

DBHandlerException::DBHandlerException(const std::string &message) : Exception("DBHandler", message)
{
}

ServerException::ServerException(const std::string &message) : Exception("Server", message)
{
}