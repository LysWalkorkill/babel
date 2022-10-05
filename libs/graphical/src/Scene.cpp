/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#include "graphical/Scene.hpp"

using namespace babel::graphical::scene;

Scene::Scene(std::string name, int width, int height) : _name(std::move(name)), _scene(new QGraphicsScene(0, 0, width, height))
{
}

Scene::~Scene()
= default;

const std::string &Scene::getName() const
{
    return _name;
}

QGraphicsScene &Scene::getScene() const
{
    return *_scene;
}

void Scene::setBackgroundColor(int r, int g, int b, int a)
{
    _scene->setBackgroundBrush(QColor(r, g, b, a));
}

void Scene::addWidget(const std::shared_ptr<IWidgets>& widget)
{
    _widgets.emplace_back(widget);
}

void Scene::addMainWidget(const std::shared_ptr<IWidgets>& widget)
{
    _scene->addWidget(widget->getWidgets());
    _mainWidget = widget;
}

std::shared_ptr<babel::graphical::IWidgets> Scene::getWidgetByID(int id) const
{
    auto elem = std::find_if(_widgets.begin(), _widgets.end(), [id](const auto &e){
        if (std::static_pointer_cast<AWidgets>(e)->getID() == id)
            return true;
        return false;
    });
    if (elem != _widgets.end())
        return *elem;
     return nullptr;
}

std::shared_ptr<babel::graphical::IWidgets> Scene::getMainWidget() const
{
    return _mainWidget;
}
