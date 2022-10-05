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

void Client::createSceneRegister()
{
    _graphical->createScene("Register", 1590, 890);
    _graphical->getScene("Register")->setBackgroundColor(31, 31, 46, 255);

    std::shared_ptr<Widget> parent = std::make_shared<Widget>();
    parent->setTransparentBackground(true);

    std::shared_ptr<QButton> backButton = std::make_shared<QButton>("Back", *parent->getWidgets());
    backButton->move(10, 840);

    backButton->setStyleSheet("background-color: #5ACBC7;\n"
                             "border-radius: 10px;\n"
                             "text-color: white;\n"
                             "font: bold 14px;\n"
                             "min-width: 10em;\n"
                             "padding: 6px;");
    backButton->connect([this](){
        _graphical->setScene("Connexion");
    });

    std::shared_ptr<QButton> registerButton = std::make_shared<QButton>("Register", *parent->getWidgets());
    registerButton->move(680, 600);

    registerButton->setStyleSheet("background-color: #5ACBC7;\n"
                                "border-radius: 15px;\n"
                                "text-color: white;\n"
                                "font: bold 14px;\n"
                                "min-width: 10em;\n"
                                "padding: 15px;");

    std::shared_ptr<Label> registerTitle = std::make_shared<Label>("Create an account on Babel", *parent->getWidgets());
    registerTitle->move(530, 200);
    registerTitle->setFont(QFont("Arial", 30, QFont::Normal));

    std::shared_ptr<LineEdit> username = std::make_shared<LineEdit>("Username", *parent->getWidgets());
    username->move(600, 350);
    username->setStyleSheet("background-color: white;\n"
                           "border-radius: 15px;"
                           "color: black;"
                           "min-width: 20em;"
                           "min-height: 2em;"
                           "padding:6px;");
    username->setPlaceholder("Username");
    username->setPlaceholderColor(QColor(Qt::gray));
    username->setMaxLength(50);

    std::shared_ptr<LineEdit> password = std::make_shared<LineEdit>("Password", *parent->getWidgets());
    password->move(600, 450);
    password->setStyleSheet("background-color: white;\n"
                           "border-radius: 15px;"
                           "color: black;"
                           "min-width: 20em;"
                           "min-height: 2em;"
                           "padding:6px;");
    password->setPlaceholder("Password");
    password->setPlaceholderColor(QColor(Qt::gray));
    password->setHiddenText(true);
    password->setMaxLength(50);

    registerButton->connect([this, username, password](){
        _graphical->setScene("Loading");
       sendRegisterReq(username->getTxt(), password->getTxt());
    });

    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addMainWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(backButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(registerButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(registerTitle);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(username);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Register"))->addWidget(password);
}