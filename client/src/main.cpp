/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** TODO: add description
*/

#include <iostream>
#include "Client.hpp"

using namespace babel::client;

int main(int argc, char **argv) try {
    Client client(argc, argv);
    client.run();
    return (0);
} catch (ClientException &e) {
    std::cerr << "{" << e.getComponent() << "} " << e.what() << std::endl;
    return 84;
} catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (84);
}
