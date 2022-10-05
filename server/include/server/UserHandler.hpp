/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** UserHandler
*/

#ifndef USERHANDLER_HPP_
#define USERHANDLER_HPP_

#include <string>
#include <vector>
#include "server/Storage.hpp"
#include "server/DBHandler.hpp"

using namespace babel::server::table;

namespace babel::server
{
    class UserHandler {
        public:
            UserHandler() = delete;
            UserHandler(DBHandler &db);
            ~UserHandler();
            UserHandler(const UserHandler &) = default;
            UserHandler &operator=(const UserHandler &) = delete;

            int insertUser(const User &user);
            int connectUser(const std::string &username, const std::string &password);
            bool disconnectUser(int id);
            std::vector<User> getUsers() const;
            User getUser(int id);

        private:
            bool userAlreadyConnected(int id) const noexcept;

        private:
            DBHandler &_db;
            std::vector<User> _loadedUsers;
    };
} // namespace babel::server



#endif /* !USERHANDLER_HPP_ */
