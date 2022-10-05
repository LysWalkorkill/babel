/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** DBHandler
*/

#ifndef DBHANDLER_HPP_
#define DBHANDLER_HPP_

#include <iostream>
#include <functional>
#include <sqlite_orm/sqlite_orm.h>

#include <boost/optional.hpp>
#include "Exception.hpp"
#include <server/Storage.hpp>

namespace babel::server
{
    class DBHandler {
        public:
            DBHandler() = delete;
            DBHandler(const std::string &db);
            ~DBHandler();
            DBHandler(const DBHandler &db) = default;
            DBHandler &operator=(const DBHandler &db) = default;

            template<typename Line>
            auto insert(Line line)
            try {
                auto col = _storage.insert(line);
                return col;
            } catch (...) {
                throw DBHandlerException("Unable to insert user");
            }

            template<typename Table>
            auto get()
            try {
                auto table = _storage.get_all<Table>();
                return table;
            } catch(const std::system_error& e) {
                throw DBHandlerException("Unable to find user");
            } catch(...) {
                throw DBHandlerException("Unable to find user");
            }

            template<typename Table>
            auto get(int id)
            try {
                auto table = _storage.get<Table>(id);
                return table;
            } catch(const std::system_error& e) {
                throw DBHandlerException("Unable to find user");
            } catch(...) {
                throw DBHandlerException("Unable to find user");
            }

            template<typename Line>
            auto update(Line line)
            {
                auto col = _storage.update(line);
                return col;
            }

            Storage &getStorage() noexcept;

        private:
            Storage _storage;
    };
} // namespace babel::server



#endif /* !DBHANDLER_HPP_ */
