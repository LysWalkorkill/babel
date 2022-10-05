/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#include "network/Exception.hpp"

using namespace babel::network;

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


QTSocketException::QTSocketException(const std::string &message) : Exception("QTSocket", message)
{
}
