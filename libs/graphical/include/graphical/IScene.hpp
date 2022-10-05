/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#ifndef ISCENE_HPP
#define ISCENE_HPP

#include <string>
#include <memory>
#include "IWidgets.hpp"

namespace babel::graphical::scene
{
    class IScene {
        public:
            virtual ~IScene() = default;

            [[nodiscard]] virtual const std::string &getName() const = 0;

            virtual void setBackgroundColor(int r, int g, int b, int a) = 0;

            virtual std::shared_ptr<IWidgets> getWidgetByID(int id) const = 0;
    };
}

#endif //ISCENE_HPP
