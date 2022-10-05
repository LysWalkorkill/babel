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

void Client::createSceneHome()
{
    _graphical->createScene("Home", 1590, 890);
    _graphical->getScene("Home")->setBackgroundColor(31, 31, 46, 255);

    std::shared_ptr<Widget> parent = std::make_shared<Widget>();
    parent->setTransparentBackground(true);

    std::shared_ptr<QButton> signOutButton = std::make_shared<QButton>("Sign Out", *parent->getWidgets());
    signOutButton->move(1400, 10);

    signOutButton->setStyleSheet("background-color: #5ACBC7;\n"
                                  "border-radius: 10px;\n"
                                  "text-color: white;\n"
                                  "font: bold 14px;\n"
                                  "min-width: 10em;\n"
                                  "padding: 6px;");
    signOutButton->connect([this](){
        sendLogoutReq();
        _graphical->setScene("Connexion");
    });

    std::shared_ptr<QButton> callButton = std::make_shared<QButton>("Unavailable", *parent->getWidgets());
    callButton->move(1400, 85);
    callButton->setSize(150, 40);
    callButton->setID(4);

    callButton->setStyleSheet("background-color: red;\n"
                                 "border-radius: 10px;\n"
                                 "text-color: white;\n"
                                 "font: bold 14px;\n"
                                 "min-width: 3em;\n"
                                 "padding: 6px;");

    std::shared_ptr<Label> contactTitle = std::make_shared<Label>("Contacts", *parent->getWidgets());
    contactTitle->move(120, 90);
    contactTitle->setSize(200, 25);
    contactTitle->setFont(QFont("Arial", 25, QFont::Normal));

    std::shared_ptr<Label> username = std::make_shared<Label>("Unknown", *parent->getWidgets());
    username->move(1220, 14);
    username->setSize(200, 20);
    username->setFont(QFont("Arial", 15, QFont::Normal));
    username->setID(1);

    std::shared_ptr<Label> selectedFriend = std::make_shared<Label>("Select a Friend", *parent->getWidgets());
    selectedFriend->move(450, 80);
    selectedFriend->setSize(200, 20);
    selectedFriend->setFont(QFont("Arial", 15, QFont::Normal));
    selectedFriend->setID(2);

    std::shared_ptr<Label> selectedFriendStatus = std::make_shared<Label>("Waiting", *parent->getWidgets());
    selectedFriendStatus->move(460, 115);
    selectedFriendStatus->setSize(200, 20);
    selectedFriendStatus->setFont(QFont("Arial", 10, QFont::Normal));
    selectedFriendStatus->setStyleSheet("color: grey;");
    selectedFriendStatus->setID(3);

    std::shared_ptr<Label> line = std::make_shared<Label>(*parent->getWidgets());
    line->setGeometry(0, 60, 1590, 5);
    line->setStyleSheet("background-color: white;");

    std::shared_ptr<Label> line2 = std::make_shared<Label>(*parent->getWidgets());
    line2->setGeometry(400, 60, 5, 1590);
    line2->setStyleSheet("background-color: white;");

    std::shared_ptr<Label> line3 = std::make_shared<Label>(*parent->getWidgets());
    line3->setGeometry(400, 150, 1190, 5);
    line3->setStyleSheet("background-color: white;");

    int x = 30;
    int y = 150;

    for (int i = 0; i < 100; i++) {
        std::shared_ptr<QButton> list = std::make_shared<QButton>("", *parent->getWidgets());
        if (i != 0)
            y += 80;
        list->move(x, y);
        list->setStyleSheet("background-color: #785acb;\n"
                                "border-radius: 1px;\n"
                                "color: white;\n"
                                "font: bold 14px;\n"
                                "min-width: 19em;\n"
                                "min-height: 3em; \n"
                                "padding: 6px;\n"
                                "Text-align:left;\n");
        list->setID(i + 5);
        list->show(false);
        std::static_pointer_cast<graphical::scene::Scene>(
            _graphical->getScene("Home"))->addWidget(list);
    }


    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addMainWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(parent);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(signOutButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(callButton);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(contactTitle);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(username);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(selectedFriend);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(selectedFriendStatus);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(line);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(line2);
    std::static_pointer_cast<graphical::scene::Scene>(
        _graphical->getScene("Home"))->addWidget(line3);
}

void Client::resetHomeScene()
{
    auto user = _graphical->getScene("Home")->getWidgetByID(1);
    auto selectedFriend = _graphical->getScene("Home")->getWidgetByID(2);
    auto selectedFriendStatus = _graphical->getScene("Home")->getWidgetByID(3);
    auto callButton = _graphical->getScene("Home")->getWidgetByID(4);
    user->setText("Unknown");
    selectedFriend->setText("Select a friend");
    selectedFriendStatus->setText("Unknown");
    std::static_pointer_cast<QButton>(callButton)->disconnectAll();
}