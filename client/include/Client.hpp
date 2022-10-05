/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <memory>
#include <algorithm>
#include <cstring>
#include <QPushButton>
#include <iostream>
#include <sstream>

#include "ClientException.hpp"
#include "graphical/GraphicalManager.hpp"
#include "graphical/GraphicalException.hpp"
#include "network/QTSocketTCP.hpp"
#include "network/QTSocketUDP.hpp"
#include "network/Protocol.hpp"
#include "audio/Audio.hpp"
#include "audio/AudioEncoder.hpp"

#include "graphical/QButton.hpp"
#include "graphical/Widget.hpp"
#include "graphical/Label.hpp"
#include "graphical/LineEdit.hpp"
#include "graphical/DialogBox.hpp"

namespace babel::client
{
    PACK(struct Contact
    {
        int id{};
        bool status{};
        char username[50] = {0};
    });

    namespace status {
        enum RequestStatus
        {
            TRY,
            RINGING,
            OK,
            USER_REGISTERED,
            USER_LOGGED_IN,
            USER_LOGGED_OUT,
            CONTACTS,
            INFO_CONTACT,
            BAD_REQUEST,
            UNAUTHORIZED,
            NOT_FOUND,
            INTERNAL_ERROR,
            UNAVAILABLE,
            INVITE, 
            ACK,
            MESSAGE, 
            CANCEL,
            BYE,
            REGISTER,
            LOGIN,
            LOGOUT,
            NOTIFY_CONTACT,
            UNDEFINED
        };
    };

    class Client {

        public:
            Client() = delete;
            Client(int &argc, char **argv);
            ~Client();
            Client(const Client &) = default;
            Client &operator=(const Client &) = default;

            int run();

        private:
            void setWindowOptions();
            void createSceneConnexion();
            void createSceneRegister();
            void createSceneHome();
            void createSceneLoading();
            void createSceneCall();
            void updateAllContacts(const std::vector<Contact> &contacts);
            void updateStatusContact(int id, int status);
            void addNewContact(const Contact &contact);
            void resetHomeScene();

            void setupConnectionServer();
            int handleRead(QByteArray data);
            void serverResponse(int code, int size, const std::string &data);

            //Event server
            void tryEvt(const std::string &data, int size);
            void ringingEvt(const std::string &data, int size);
            void okEvt(const std::string &data, int size);
            void userRegisteredEvt(const std::string &data, int size);
            void userLoggedInEvt(const std::string &data, int size);
            void userLoggedOutEvt(const std::string &data, int size);
            void contactsEvt(const std::string &data, int size);
            void infoContactEvt(const std::string &data, int size);
            void badRequestEvt(const std::string &data, int size);
            void unauthorizedEvt(const std::string &data, int size);
            void notFoundEvt(const std::string &data, int size);
            void internalErrorEvt(const std::string &data, int size);
            void unavailableEvt(const std::string &data, int size);
            void contactNotificationEvt(const std::string &data, int size);
            void ackEvt(const std::string &data, int size);
            void byeEvt(const std::string &data, int size);
            void inviteEvt(const std::string &data, int size);
            void unknownEvt(const std::string &data, int size);
            void cancelEvt(const std::string &data, int size);

            void sendInviteReq(int id);
            void sendAckReq();
            void sendMessageReq();
            void sendCancelReq();
            void sendByeReq();
            void sendRegisterReq(const std::string &username, const std::string &password);
            void sendLoginReq(const std::string &login, const std::string &password);
            void sendLogoutReq();
            void sendContactsReq();
            void sendContactInfoReq(int id);
            void sendRingingReq();
            void sendOkReq();

            std::string binaryIPV4ToString(const std::string &adress) const;

            void startAudio();
            void stopAudio();
            void stopUDP();
            void startSocketUDP();
            void reconnectClient();
            void stopAudioAndUDP();

        private:
            std::shared_ptr<graphical::IGraphical> _graphical;
            std::unique_ptr<network::ISocket> _socket;
            std::shared_ptr<network::ISocket> _socketUDP;
            std::vector<std::pair<Contact, int>> _contactsID;
            std::unique_ptr<audio::IAudio> _audio;
            std::shared_ptr<audio::IAudioEncoder> _audioEncoder;
            bool _waitForOk = false;
            status::RequestStatus _status = status::UNDEFINED;
    };
}

#endif //BABEL_CLIENT_CLIENT_HPP
