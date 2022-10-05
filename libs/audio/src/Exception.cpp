/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Exception
*/

#include "audio/Exception.hpp"

using namespace babel::audio;

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


AudioException::AudioException(const std::string &message) : Exception("Audio", message)
{
}
