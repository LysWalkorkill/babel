/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Storage
*/

#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <sqlite_orm/sqlite_orm.h>

namespace babel::server
{
    namespace table
    {
        struct User
        {
            User()
            {
                username.resize(50, 0);
                password.resize(50, 0);
            };

            User(int id_, const std::string &user, const std::string &pass, bool connect = false)
            {
                id = id_;
                username.resize(50, 0);
                password.resize(50, 0);
                std::copy_n(user.begin(), user.size(), username.begin());
                std::copy_n(pass.begin(), pass.size(), password.begin());
                connected = connect;
            };

            User(const User &user)
            {
                id = user.id;
                username.resize(50, 0);
                password.resize(50, 0);
                std::copy_n(user.username.begin(), user.username.size(), username.begin());
                std::copy_n(user.password.begin(), user.password.size(), password.begin());
                connected = user.connected;
            };

            User &operator=(const User &user)
            {
                id = user.id;
                username.resize(50, 0);
                password.resize(50, 0);
                std::copy_n(user.username.begin(), user.username.size(), username.begin());
                std::copy_n(user.password.begin(), user.password.size(), password.begin());
                connected = user.connected;
                return (*this);
            };

            int id;
            std::string username;
            std::string password;
            bool connected = false;
        };
    };
};

inline auto initStorage(const std::string &dbName){
    return sqlite_orm::make_storage(dbName, sqlite_orm::make_table(
        "users",
        sqlite_orm::make_column("id", &babel::server::table::User::id, sqlite_orm::autoincrement(), sqlite_orm::primary_key()),
        sqlite_orm::make_column("username", &babel::server::table::User::username, sqlite_orm::unique()),
        sqlite_orm::make_column("password", &babel::server::table::User::password)
    ));
}

using Storage = decltype(initStorage(""));

#endif /* !STORAGE_HPP_ */
