/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef IGRAPHICAL_HPP
#define IGRAPHICAL_HPP

#include "IScene.hpp"

namespace babel::graphical {

    class IGraphical {
    public:
        virtual ~IGraphical() = default;

        /* EXECUTION */
        virtual int exec() = 0;
        virtual void show() = 0;

        /* WINDOWS */
        virtual void setWindowTitle(const std::string &name) = 0;
        virtual void setWindowFixedSize(int width, int height) = 0;

        /* SCENE */
        virtual void createScene(const std::string &name, int width, int height) = 0;
        virtual void removeScene(const std::string &name) = 0;
        virtual void setScene(const std::string &name) = 0;
        virtual std::shared_ptr<scene::IScene> getScene(const std::string &name) = 0;
        [[nodiscard]] virtual const std::string &getCurrentScene() const = 0;

        /* SPLASHSCREEN */
        virtual void createSplashScreen(const std::string &img, int milliseconds) = 0;
    };
}

#endif //IGRAPHICAL_HPP
