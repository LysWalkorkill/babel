/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Client
*/

#include "Client.hpp"

using namespace babel::client;
using namespace babel::network;
using namespace babel::audio;
using namespace babel::graphical;

void Client::createSceneLoading()
{
    _graphical->createScene("Loading", 1590, 890);
    _graphical->getScene("Loading")->setBackgroundColor(31, 31, 46, 255);

    std::shared_ptr<Widget> parent = std::make_shared<Widget>();
    parent->setTransparentBackground(true);

    std::shared_ptr<Label> registerTitle = std::make_shared<Label>("LOADING...", *parent->getWidgets());
    registerTitle->move(620, 400);
    registerTitle->setFont(QFont("Arial", 50, QFont::Bold));

    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Loading"))->addMainWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Loading"))->addWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Loading"))->addWidget(registerTitle);
}