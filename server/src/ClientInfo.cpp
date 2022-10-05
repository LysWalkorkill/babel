/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Client
*/

#include "server/ClientInfo.hpp"

using namespace babel::server;
using namespace babel::network;

ClientInfo::ClientInfo(boost::shared_ptr<network::ISocket> &socket):
    socket(socket)
{}
