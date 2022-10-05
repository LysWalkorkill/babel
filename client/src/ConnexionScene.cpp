/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Client
*/

#include <graphical/DialogBox.hpp>
#include "Client.hpp"

using namespace babel::client;
using namespace babel::network;
using namespace babel::audio;
using namespace babel::graphical;

void Client::createSceneConnexion()
{
    _graphical->createScene("Connexion", 1590, 890);
    _graphical->getScene("Connexion")->setBackgroundColor(31, 31, 46, 255);

    std::shared_ptr<Widget> parent = std::make_shared<Widget>();
    parent->setTransparentBackground(true);

    std::shared_ptr<Label> connectTitle = std::make_shared<Label>("Babel", *parent->getWidgets());
    connectTitle->move(720, 200);
    connectTitle->setFont(QFont("Arial", 30, QFont::Bold));

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

    std::shared_ptr<QButton> quitButton = std::make_shared<QButton>("Exit", *parent->getWidgets());
    quitButton->move(10, 840);

    quitButton->setStyleSheet("background-color: #5ACBC7;\n"
                             "border-radius: 10px;\n"
                             "text-color: white;\n"
                             "font: bold 14px;\n"
                             "min-width: 10em;\n"
                             "padding: 6px;");
    std::static_pointer_cast<GraphicalManager>(_graphical)->connectToApp(quitButton->getWidgets(), SIGNAL(clicked()), SLOT(quit()));

    std::shared_ptr<QButton> registerButton = std::make_shared<QButton>("Registration", *parent->getWidgets());
    registerButton->move(1400, 10);

    registerButton->setStyleSheet("background-color: #5ACBC7;\n"
                                 "border-radius: 10px;\n"
                                 "text-color: white;\n"
                                 "font: bold 14px;\n"
                                 "min-width: 10em;\n"
                                 "padding: 6px;");
    registerButton->connect([this]() {
        _graphical->setScene("Register");
    });

    std::shared_ptr<QButton> connectButton = std::make_shared<QButton>("Sign in", *parent->getWidgets());
    connectButton->move(680, 600);

    connectButton->setStyleSheet("background-color: #5ACBC7;\n"
                                "border-radius: 15px;\n"
                                "text-color: white;\n"
                                "font: bold 14px;\n"
                                "min-width: 10em;\n"
                                "padding: 15px;");

    connectButton->connect([this, username, password]() {
        _graphical->setScene("Loading");
        sendLoginReq(username->getTxt(), password->getTxt());
    });

    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addMainWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(connectTitle);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(username);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(password);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(quitButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(registerButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Connexion"))->addWidget(connectButton);
}