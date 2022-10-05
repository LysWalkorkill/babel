/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef GRAPHICALMANAGER_HPP
#define GRAPHICALMANAGER_HPP

#include <QApplication>
#include <QGraphicsView>
#include <memory>
#include <map>
#include <QtWidgets/QSplashScreen>
#include "IGraphical.hpp"
#include "Scene.hpp"
#include "GraphicalException.hpp"

namespace babel::graphical
{
    class GraphicalManager : public IGraphical {
        public:
            GraphicalManager(int &argc, char **argv);
            ~GraphicalManager() override;
            GraphicalManager(const GraphicalManager &) = delete;
            GraphicalManager &operator=(const GraphicalManager &) = delete;

            /* EXECUTION */
            int exec() override;
            void show() override;

            /* WINDOWS */
            void setWindowTitle(const std::string &name) override;
            void setWindowFixedSize(int width, int height) override;

            /* SCENE */
            void createScene(const std::string &name, int width, int height) override;
            void removeScene(const std::string &name) override;
            void setScene(const std::string &name) override;
            std::shared_ptr<scene::IScene> getScene(const std::string &name) override;
            [[nodiscard]] const std::string &getCurrentScene() const override;

            /* SPLASHSCREEN */
            void createSplashScreen(const std::string &img, int milliseconds) override;

            /* CONNECT */
            void connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member);
            void connectToApp(const QObject *sender, const char *signal, const char *member);

        private:
            QApplication *_app;
            QGraphicsView *_view;
            std::map<std::string, std::shared_ptr<scene::IScene>> _scenes;
            std::string _currentScene;

            /* SPLASHSCREEN */
            QSplashScreen *_splashscreen;
    };
}

#endif //GRAPHICALMANAGER_HPP
