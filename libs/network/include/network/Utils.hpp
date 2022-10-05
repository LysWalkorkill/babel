/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <QObject>

namespace babel::network
{
    class Utils {
        public:

            static const std::string toStdString(const QByteArray &data);

    };
} // namespace babel::network



#endif /* !UTILS_HPP_ */
