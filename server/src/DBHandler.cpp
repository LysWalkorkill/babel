/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** DBHandler
*/

#include "server/DBHandler.hpp"

using namespace babel::server;

DBHandler::DBHandler(const std::string &dbName) : _storage(initStorage(dbName))
{
    _storage.sync_schema();
}

DBHandler::~DBHandler()
{
}

Storage &DBHandler::getStorage() noexcept
{
    return (_storage);
}
