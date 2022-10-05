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

#ifndef RESOURCES_PATH
    #define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str)).c_str()

void Client::updateAllContacts(const std::vector<Contact> &contacts)
{
    int i = 5;

    _contactsID.clear();
    auto selectedFriend = _graphical->getScene("Home")->getWidgetByID(2);
    auto selectedFriendStatus = _graphical->getScene("Home")->getWidgetByID(3);
    auto callButton = _graphical->getScene("Home")->getWidgetByID(4);
    selectedFriend->setText("Select a friend");
    selectedFriendStatus->setText("Unknown");
    std::static_pointer_cast<QButton>(callButton)->disconnectAll();

    for (const auto &contact : contacts) {
        auto contactUI = _graphical->getScene("Home")->getWidgetByID(i);
        std::pair<Contact, int> contactInfos(contact, i);

        contactUI->setText(contact.username);
        contactUI->show(true);
        if (contact.status)
            std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("greenDot.png"));
        else
            std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("redDot.png"));

        std::static_pointer_cast<QButton>(contactUI)->disconnectAll();
        std::static_pointer_cast<QButton>(contactUI)->connect([this, contactInfos](){
            auto selectedFriend = _graphical->getScene("Home")->getWidgetByID(2);
            auto selectedFriendStatus = _graphical->getScene("Home")->getWidgetByID(3);
            auto callButton = _graphical->getScene("Home")->getWidgetByID(4);

            selectedFriend->setText(contactInfos.first.username);
            std::static_pointer_cast<QButton>(callButton)->disconnectAll();
            if (contactInfos.first.status) {
                selectedFriendStatus->setText("Available");
                callButton->setText("Call");
                callButton->setStyleSheet("background-color: green;\n"
                                          "border-radius: 10px;\n"
                                          "text-color: white;\n"
                                          "font: bold 14px;\n"
                                          "min-width: 3em;\n"
                                          "padding: 6px;");
                std::static_pointer_cast<QButton>(callButton)->connect(
                    [this, contactInfos]() {
                        _graphical->getScene("Call")->getWidgetByID(1)->setText(contactInfos.first.username);
                        _graphical->setScene("Call");
                        sendInviteReq(contactInfos.first.id);
                    });
            } else {
                selectedFriendStatus->setText("Offline");
                callButton->setText("Unavailable");
                callButton->setStyleSheet("background-color: red;\n"
                                          "border-radius: 10px;\n"
                                          "text-color: white;\n"
                                          "font: bold 14px;\n"
                                          "min-width: 3em;\n"
                                          "padding: 6px;");
            }
        });
        _contactsID.emplace_back(contactInfos);
        i++;
        if (i > 100)
            break;
    }
}

void Client::updateStatusContact(int id, int status)
{
    const auto &contactInfos = std::find_if(_contactsID.begin(), _contactsID.end(), [id](const auto &contact){
        if (contact.first.id == id)
            return true;
        return false;
    });
    if (contactInfos == _contactsID.end())
        return;
    contactInfos->first.status = status;
    const auto &contactUI = _graphical->getScene("Home")->getWidgetByID(contactInfos->second);
    if (status)
        std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("greenDot.png"));
    else
        std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("redDot.png"));
}

void Client::addNewContact(const Contact &contact)
{
    int i = 0;

    if (_contactsID.empty())
        i = 0;
    else
        i = _contactsID.back().second + 1;
    if (i >= 100)
        return;
    auto contactUI = _graphical->getScene("Home")->getWidgetByID(i);
    std::pair<Contact, int> contactInfos(contact, i);

    contactUI->setText(contact.username);
    contactUI->show(true);
    if (contact.status)
        std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("greenDot.png"));
    else
        std::static_pointer_cast<QButton>(contactUI)->setIcon(RESSOURCE("redDot.png"));

    std::static_pointer_cast<QButton>(contactUI)->disconnectAll();
    std::static_pointer_cast<QButton>(contactUI)->connect([this, contactInfos](){
        auto selectedFriend = _graphical->getScene("Home")->getWidgetByID(2);
        auto selectedFriendStatus = _graphical->getScene("Home")->getWidgetByID(3);
        auto callButton = _graphical->getScene("Home")->getWidgetByID(4);

        selectedFriend->setText(contactInfos.first.username);
        std::static_pointer_cast<QButton>(callButton)->disconnectAll();
        if (contactInfos.first.status) {
            selectedFriendStatus->setText("Available");
            callButton->setText("Call");
            callButton->setStyleSheet("background-color: green;\n"
                                      "border-radius: 10px;\n"
                                      "text-color: white;\n"
                                      "font: bold 14px;\n"
                                      "min-width: 3em;\n"
                                      "padding: 6px;");
            std::static_pointer_cast<QButton>(callButton)->connect(
                [this, contactInfos]() {
                    _graphical->getScene("Call")->getWidgetByID(1)->setText(contactInfos.first.username);
                    _graphical->setScene("Call");
                    sendInviteReq(contactInfos.first.id);
                });
        } else {
            selectedFriendStatus->setText("Offline");
            callButton->setText("Unavailable");
            callButton->setStyleSheet("background-color: red;\n"
                                      "border-radius: 10px;\n"
                                      "text-color: white;\n"
                                      "font: bold 14px;\n"
                                      "min-width: 3em;\n"
                                      "padding: 6px;");
        }
    });
    _contactsID.emplace_back(contactInfos);
}
