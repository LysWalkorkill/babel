/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Utils
*/

#include "network/Utils.hpp"

using namespace babel::network;

const std::string Utils::toStdString(const QByteArray &array)
{
    std::string data;

    for (int i = 0; i < array.size(); i++) {
        data.append(std::string(1, array.at(i)));
    }
    return (data);
}