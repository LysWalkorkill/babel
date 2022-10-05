/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** main
*/

#include "server/Exception.hpp"
#include "server/ServerHandler.hpp"
#include <exception>
#include <iostream>
#include <string>

using namespace babel::server;

short getPort(int argc, char const *argv[])
{
    int port = 0;

    if (argc != 2) {
        throw ServerException(std::string(argv[0]) + " [PORT]");
    }
    try {
        port = std::stod(argv[1]);
        if (port < 0 || port >= 65535)
            throw ServerException("Invalid port");
    } catch (const std::exception &e) {
        throw ServerException(std::string(argv[0]) + ": Invalid port");
    }
    return port;
}

int main(int argc, char const *argv[])
{
    short port = 0;

    try {
        port = getPort(argc, argv);
        ServerHandler serverHandler(port);
        serverHandler.run();
    } catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
