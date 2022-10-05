/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#include <iostream>
#include <QTimer>
#include "graphical/GraphicalManager.hpp"

#ifndef RESOURCES_PATH
    #define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str)).c_str()

using namespace babel::graphical;

GraphicalManager::GraphicalManager(int &argc, char **argv) : _app(new QApplication(argc, argv)), _view(new QGraphicsView()), _splashscreen(new QSplashScreen())
{

}

GraphicalManager::~GraphicalManager()
{
    delete _app;
}

int GraphicalManager::exec()
{
    //_app->processEvents();
    return _app->exec();
}

void GraphicalManager::show()
{
    _view->show();
}

void GraphicalManager::createScene(const std::string &name, int width, int height)
{
    if (_scenes.find(name) != _scenes.end())
        throw GraphicalException("createScene", "Scene " + name + " already exists.");
    _scenes[name] = std::make_shared<scene::Scene>(name, width, height);
}

void GraphicalManager::removeScene(const std::string &name)
{
    _scenes.erase(name);
}

void GraphicalManager::setScene(const std::string& name)
{
    if (_scenes.find(name) == _scenes.end())
        throw GraphicalException("setScene", "Scene " + name + " not found.");
    _view->setScene(&std::static_pointer_cast<scene::Scene>(_scenes.at(name))->getScene());
    _currentScene = name;
}

std::shared_ptr<scene::IScene> GraphicalManager::getScene(const std::string &name)
{
    if (_scenes.find(name) == _scenes.end())
        throw GraphicalException("getScene", "Scene " + name + " not found.");
    return _scenes.at(name);
}

void GraphicalManager::setWindowTitle(const std::string& name)
{
    _view->setWindowTitle(name.c_str());
}

void GraphicalManager::createSplashScreen(const std::string &img, int milliseconds)
{
    QPixmap pixmap(RESSOURCE(img));

    _splashscreen->setPixmap(pixmap);
    _splashscreen->show();

    QTimer::singleShot(milliseconds, _splashscreen, &QWidget::close); // keep displayed for 5 seconds
    QTimer::singleShot(milliseconds, _view, &QWidget::show); // keep displayed for 5 seconds
}

void GraphicalManager::setWindowFixedSize(int width, int height)
{
    _view->setFixedSize(width, height);
}

void GraphicalManager::connect(const QObject *sender, const char *signal, const QObject *receiver, const char *member)
{
    QObject::connect(sender, signal, receiver, member);
}

void GraphicalManager::connectToApp(const QObject *sender, const char *signal, const char *member)
{
    QObject::connect(sender, signal, _app, member);
}

const std::string &GraphicalManager::getCurrentScene() const
{
    return _currentScene;
}

