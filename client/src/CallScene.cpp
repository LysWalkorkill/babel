/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Client
*/

#include "Client.hpp"

#ifndef RESOURCES_PATH
    #define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str)).c_str()

using namespace babel::client;
using namespace babel::network;
using namespace babel::audio;
using namespace babel::graphical;

void Client::createSceneCall()
{
    _graphical->createScene("Call", 1590, 890);
    _graphical->getScene("Call")->setBackgroundColor(31, 31, 46, 255);

    std::shared_ptr<Widget> parent = std::make_shared<Widget>();
    parent->setTransparentBackground(true);

    std::shared_ptr<Label> avatar = std::make_shared<Label>(*parent->getWidgets());
    avatar->setImage(RESSOURCE("avatar.png"));
    avatar->setSize(200, 200);
    avatar->move(665, 200);

    std::shared_ptr<Label> userCalled = std::make_shared<Label>("Unknown", *parent->getWidgets());
    userCalled->setID(1);
    userCalled->move(680, 500);
    userCalled->setFont(QFont("Arial", 30, QFont::Normal));

    std::shared_ptr<QButton> hangup = std::make_shared<QButton>("Hang up", *parent->getWidgets());
    hangup->setID(2);
    hangup->move(680, 700);
    hangup->setStyleSheet("background-color: red;\n"
                          "border-radius: 10px;\n"
                          "text-color: white;\n"
                          "font: bold 14px;\n"
                          "min-width: 8em;\n"
                          "padding: 10px;");
    hangup->connect([this](){
        _graphical->setScene("Home");
        sendByeReq();
    });

    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Call"))->addMainWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Call"))->addWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Call"))->addWidget(avatar);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Call"))->addWidget(userCalled);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Call"))->addWidget(hangup);
}