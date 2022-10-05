/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** UserHandler
*/

#include "server/UserHandler.hpp"

using namespace babel::server;
using namespace sqlite_orm;

UserHandler::UserHandler(DBHandler &db) : _db(db)
{
}

UserHandler::~UserHandler()
{
}

int UserHandler::insertUser(const User &user)
try {
    int id = _db.insert<User>(user);
    _loadedUsers.emplace_back<User>({id, user.username, user.password, true});
    return (id);
} catch (const DBHandlerException &e) {
    return (-1);
}

int UserHandler::connectUser(const std::string &username, const std::string &password)
try {
    Storage &storage = _db.getStorage();

    auto users = storage.get_all<User>(where(c(&User::username) == username and c(&User::password) == password));
    
    int id = -1;

    for (const auto &user : users) {
        id = user.id;
        if (userAlreadyConnected(id))
            return (-1);
        User u(user);
        _loadedUsers.emplace_back<User>({u.id, u.username, u.password});
    }
    return id;
} catch(const std::system_error& e) {
    return (-1);
} catch(...) {
    return (-1);
}

bool UserHandler::disconnectUser(int id)
{
    auto user = std::find_if(_loadedUsers.begin(), _loadedUsers.end(), [id](const User &user) {
        return (user.id == id);
    });
    if (user != _loadedUsers.end())
        _loadedUsers.erase(user);
    return true;
}

std::vector<User> UserHandler::getUsers() const
{
    std::vector<User> allUsers = _db.get<User>();

    std::for_each(allUsers.begin(), allUsers.end(), [this](User &user) {
        if (userAlreadyConnected(user.id)) {
            user.connected = true;
        } else {
            user.connected = false;
        }
    });
    return (allUsers);
}

User UserHandler::getUser(int id)
try {
    return (_db.get<User>(id));
} catch (const DBHandlerException &e) {
    return (User{-1, "", ""});
}

bool UserHandler::userAlreadyConnected(int id) const noexcept
{
    return (
        _loadedUsers.end() != std::find_if(_loadedUsers.begin(), _loadedUsers.end(), [&id](const User &user) {
            return (id == user.id);
        })
    );
}