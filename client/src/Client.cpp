/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Client
*/

#include "Client.hpp"
#include "ClientException.hpp"

using namespace babel::client;
using namespace babel::network;
using namespace babel::audio;
using namespace babel::graphical;

Client::Client(int &argc, char **argv) : 
    _graphical(std::make_unique<graphical::GraphicalManager>(argc, argv)),
    _socket(nullptr)
{
    int port = 0;

    if (argc != 3) {
        throw ClientException("Arguments", std::string(argv[0]) + " [IP] [PORT]");
    }
    try {
        port = std::stod(argv[2]);
        if (port < 0 || port >= 65535)
            throw ClientException("Arguments", "Invalid port");
    } catch (const std::exception &e) {
        throw ClientException("Arguments", std::string(argv[0]) + ": Invalid port");
    }

    _socket = std::make_unique<QTSocketTCP>(argv[1], port);
}

Client::~Client() = default;

int Client::run()
{
    setupConnectionServer();
    setWindowOptions();

    _graphical->createSplashScreen("splashscreen.png", 5000);
    createSceneConnexion();
    createSceneRegister();
    createSceneHome();
    createSceneLoading();
    createSceneCall();

    _graphical->setScene("Connexion");

    return _graphical->exec();
}

void Client::setWindowOptions()
{
    _graphical->setWindowTitle("Babel");
    _graphical->setWindowFixedSize(1600, 900);
}

void Client::setupConnectionServer()
{
    _socket->setReadFct([this](const std::string &data) -> int {
        struct Header header = {0};

        if (data.size() < sizeof(Header)) {
            return (0);
        }
        std::memcpy(&header, data.c_str(), sizeof(Header));
        if (header.messageSize + sizeof(Header) > data.size()) {
            return (0);
        }
        std::string message(header.messageSize, 0);
        std::copy_n(data.begin() + sizeof(Header), header.messageSize, message.begin());
        // std::cout << "Receive : " << std::flush;
        // ::write(1, data.c_str(), header.messageSize + sizeof(Header));
        // std::cout << std::endl;
        this->serverResponse(header.nb, header.messageSize, message);
        return sizeof(Header) + header.messageSize;
    });
}

int Client::handleRead(QByteArray data)
{
    return (0);
}

void Client::serverResponse(int code, int size, const std::string &data)
{
    std::map<int, void (Client::*)(const std::string &, int)> events = {
        {response::TRY, &Client::tryEvt},
        {response::RINGING, &Client::ringingEvt},
        {response::OK, &Client::okEvt},
        {response::USER_REGISTERED, &Client::userRegisteredEvt},
        {response::USER_LOGGED_IN, &Client::userLoggedInEvt},
        {response::CONTACTS, &Client::contactsEvt},
        {response::INFO_CONTACT, &Client::infoContactEvt},
        {response::BAD_REQUEST, &Client::badRequestEvt},
        {response::UNAUTHORIZED, &Client::unauthorizedEvt},
        {response::NOT_FOUND, &Client::notFoundEvt},
        {response::INTERNAL_ERROR, &Client::internalErrorEvt},
        {response::UNAVAILABLE, &Client::unavailableEvt},
        {response::USER_LOGGED_OUT, &Client::userLoggedOutEvt},
        {request::NOTIFY_CONTACT, &Client::contactNotificationEvt},
        {request::INVITE, &Client::inviteEvt},
        {request::ACK, &Client::ackEvt},
        {request::BYE, &Client::byeEvt},
        {request::CANCEL, &Client::cancelEvt}
    };

    if (events.count(code))
        return (this->*events[code])(data, size);
    unknownEvt(data, size);
}

void Client::tryEvt(const std::string &data, int size)
{
    //TODO:
    // ? Se préparer à la prochaine requête
    std::cout << "{CLIENT} receive try event" << std::endl;
    _status = status::UNDEFINED;
}

void Client::ringingEvt(const std::string &data, int size)
{
    //TODO:
    /*
    * 1 - Récupérer l'Adresse IPV6 et le port
    * 2 - Set l'adresse IPV6 et le port dans socket UDP
    * 3 - Attendre la requête ok
    */
    std::cout << "{CLIENT} receive ringing event" << std::endl;
    std::string binaryIPV6(4, '\0');
    unsigned short port;

    std::memcpy(binaryIPV6.data(), data.c_str(), 4);
    std::memcpy(&port, data.c_str() + 4, sizeof(short));
    std::string ipv4Str = binaryIPV4ToString(binaryIPV6);

    if (_socketUDP == nullptr)
        return;
    static_cast<QTSocketUDP *>(_socketUDP.get())->setReceiverInfo(ipv4Str, port);
    std::cout << "Receiver info " << ipv4Str << " and port " << port << std::endl;
    _waitForOk = true;
    _status = status::UNDEFINED;
}

void Client::okEvt(const std::string &data, int size)
{
    //TODO:
    /*
    * Si en attente du ok -> envoyer ACK et ouvrir l'audio
    */
    std::cout << "{CLIENT} receive ok event" << std::endl;
    if (_waitForOk) {
        startAudio();
        sendAckReq();
        _waitForOk = false;
    } else {
        _status = status::UNDEFINED;
    }
}

void Client::cancelEvt(const std::string &data, int size)
{
    //TODO:
    /*
    * Si en attente du ok -> envoyer ACK et ouvrir l'audio
    */
    std::cout << "{CLIENT} receive cancel event" << std::endl;
    stopAudioAndUDP();
    _graphical->setScene("Home");
    Header header = {response::OK, 0};
    std::string request;

    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    _socket->write(request);
}

void Client::userRegisteredEvt(const std::string &data, int size)
{
    /*
    * CODE : 220
    * DATA : 0
    * 1 - Changé de scène directement
    * 2 - Request au serveur pour récupérer la liste des contacts
    */
    std::cout << "{CLIENT} receive user registered event" << std::endl;
    resetHomeScene();
    _graphical->getScene("Home")->getWidgetByID(1)->setText(data);
    _graphical->setScene("Home");
}

void Client::userLoggedOutEvt(const std::string &data, int size)
{
    std::cout << "{CLIENT} receive user logged out event" << std::endl;
    _graphical->setScene("Connexion");
    _status = status::UNDEFINED;
}

void Client::userLoggedInEvt(const std::string &data, int size)
{
    std::cout << "{CLIENT} receive user logged in event" << std::endl;
    // std::cout << size << std::endl;
    resetHomeScene();
    _graphical->getScene("Home")->getWidgetByID(1)->setText(data.c_str());
    _graphical->setScene("Home");
}

void Client::contactsEvt(const std::string &data, int size)
{
    //TODO:
    /*
    * CODE : 240
    * DATA : 
    */
    std::cout << "{CLIENT} receive contacts event" << std::endl;
    std::vector<Contact> contacts;

    // std::cout << size << std::endl;
    for (int i = 0; i < size; i += sizeof(Contact)) {
        Contact contact = {0};

        std::memcpy(&contact, data.c_str() + i, sizeof(Contact));
        // std::cout << "Receive : " << contact.username << std::endl;
        contacts.push_back(contact);
    }
    updateAllContacts(contacts);
    _status = status::UNDEFINED;
}

void Client::infoContactEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive info contact event" << std::endl;
    Contact contact = {0};

    std::memcpy(&contact, data.c_str(), sizeof(Contact));
    addNewContact(contact);
    _status = status::UNDEFINED;
}

void Client::badRequestEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive bad request event" << std::endl;
    if (_status == status::REGISTER) {
        DialogBox badRequest("Bad Request", "Server can't register a account with this username and password", DialogBox::Dlevel::CRITICAL);
        _graphical->setScene("Register");
    } else if (_status == status::LOGIN) {
        DialogBox badRequest("Bad Request", "Wrong username and/or password", DialogBox::Dlevel::CRITICAL);
        _graphical->setScene("Connexion");
    } else if (_status == status::LOGOUT) {
        DialogBox badRequest("Bad Request", "Failed to logged out account", DialogBox::Dlevel::CRITICAL);
        _graphical->setScene("Home");
    } else if (_status == status::BYE) {
        DialogBox badRequest("Bad Request", "You can't send bye to an account who is not in call", DialogBox::Dlevel::CRITICAL);
    } else if (_status == status::CANCEL) {
        DialogBox badRequest("Bad Request", "Can't cancel the call", DialogBox::Dlevel::CRITICAL);
    } else if (_status == status::INVITE) {
        DialogBox badRequest("Bad Request", "You can't call this account", DialogBox::Dlevel::CRITICAL);
        stopAudioAndUDP();
        _graphical->setScene("Home");
    } else if (_status == status::RINGING) {
        DialogBox badRequest("Bad Request", "You can't call this account", DialogBox::Dlevel::CRITICAL);
        stopAudioAndUDP();
        _graphical->setScene("Home");
    } else if (_status == status::OK) {
        DialogBox badRequest("Bad Request", "You can't call this account", DialogBox::Dlevel::CRITICAL);
        stopAudioAndUDP();
        _graphical->setScene("Home");
    } else {
        DialogBox badRequest("Bad Request", "Bad request", DialogBox::Dlevel::CRITICAL);
    }
    _status = status::UNDEFINED;
}

void Client::unauthorizedEvt(const std::string &data, int size)
{
    //TODO:
    DialogBox unauthorizedEvt("Unauthorized Event", "You must connect to an account before using this service", DialogBox::Dlevel::WARNING);
    std::cout << "{CLIENT} receive unauthorized event" << std::endl;
    // _graphical->displayUnauthorized();
    _status = status::UNDEFINED;
}

void Client::notFoundEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive not found event" << std::endl;
    if (_status == status::LOGIN) {
        DialogBox notFound("Not Found", "Wrong username or password", DialogBox::Dlevel::INFORMATION);
        _graphical->setScene("Connexion");
    } else if (_status == status::INVITE) {
        DialogBox notFound("Not Found", "User not found", DialogBox::Dlevel::INFORMATION);
        _graphical->setScene("Home");
    } else {
        DialogBox notFound("Not Found", "Receive not found error", DialogBox::Dlevel::INFORMATION);
    }
    _status = status::UNDEFINED;
}

void Client::internalErrorEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive internal error event" << std::endl;
    // _graphical->displayInternalError();
    DialogBox critical("Critical error", "Server send internal error", DialogBox::Dlevel::CRITICAL);
    stopAudioAndUDP();
    _graphical->setScene("Home");
    _status = status::UNDEFINED;
}

void Client::unavailableEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive unavailable event" << std::endl;
    // _graphical->displayUnavailable();
    DialogBox unavailableEvt("Unavailable Event", "The client is unavailable", DialogBox::Dlevel::INFORMATION);
    stopAudioAndUDP();
    _graphical->setScene("Home");

    _status = status::UNDEFINED;
}

void Client::contactNotificationEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive contact notification event" << std::endl;
    int id;
    bool status;

    std::memcpy(&id, data.c_str(), 4);
    std::memcpy(&status, data.c_str() + 4, 1);
    updateStatusContact(id, status);
    _status = status::UNDEFINED;
}

void Client::ackEvt(const std::string &data, int size)
{
    //TODO:
    std::cout << "{CLIENT} receive ack event" << std::endl;
    startAudio();
    _status = status::UNDEFINED;
}

void Client::byeEvt(const std::string &data, int size)
{
    /*
    * 1 - Arréter l'audio
    * 2 - Arréter la socket UDP
    * 3 - Envoyer message au graphics
    */
    std::cout << "{CLIENT} receive bye event" << std::endl;
    stopAudioAndUDP();
    sendOkReq();
    _graphical->setScene("Home");
}

void Client::inviteEvt(const std::string &data, int size)
{
    //TODO:
    /*
    * 1 - Récuper l'id et l'IPV6
    * 2 - Afficher call sur le graphique
    * 3 - Démarrer SocketUDP
    * 4 - Envoyer ringing avec adresse IPV6 et le port au serveur
    */
    std::cout << "{CLIENT} receive invite event" << std::endl;
    std::string binaryIPV4(4, '\0');
    unsigned short port;
    int id;

    std::memcpy(&id, data.c_str(), 4);
    std::memcpy(binaryIPV4.data(), data.c_str() + 4, 4);
    std::memcpy(&port, data.c_str() + 8, sizeof(short));
    std::string ipv4Str = binaryIPV4ToString(binaryIPV4);

    startSocketUDP();

    auto user = std::find_if(_contactsID.begin(), _contactsID.end(), [id](const std::pair<Contact, int> &contact) {
        return contact.first.id == id;
    });
    if (user != _contactsID.end()) {
        _graphical->getScene("Call")->getWidgetByID(1)->setText(user->first.username);
    }

    std::cout << "Receiver info " << ipv4Str << " and port " << port << std::endl;
    if (_socketUDP == nullptr)
        return;
    static_cast<QTSocketUDP *>(_socketUDP.get())->setReceiverInfo(ipv4Str, port);
    sendRingingReq();
    sendOkReq();
    _graphical->setScene("Call");
}

void Client::unknownEvt(const std::string &data, int size)
{
    std::cout << "{CLIENT} receive unknown event" << std::endl;
}

void Client::sendContactsReq()
{
    std::cout << "{CLIENT} send contact request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::CONTACTS, 0};
    std::string request(sizeof(Header), '\0');

    std::memcpy(request.data(), &header, sizeof(Header));
    _socket->write(request);
    _status = status::CONTACTS;
}

void Client::sendInviteReq(int id)
{
    //TODO:
    /*
    * 1 - Connecter Socket UDP
    * 2 - Récupérer port
    * 3 - Envoyer info aux serveurs
    */
    std::cout << "{CLIENT} send invite request" << std::endl;
    std::cout << "Call " << id << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    startSocketUDP();
    if (_socketUDP == nullptr)
        return;
    short port = static_cast<QTSocketUDP *>(_socketUDP.get())->getPort();

    Header header = {request::INVITE, sizeof(int) + sizeof(short)};
    std::string request;

    request.reserve(sizeof(Header) + header.messageSize);
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    request.append(reinterpret_cast<char *>(&id), sizeof(int));
    request.append(reinterpret_cast<char *>(&port), sizeof(short));
    _socket->write(request);
    _status = status::INVITE;
}

void Client::sendAckReq()
{
    //TODO:
    std::cout << "{CLIENT} send ack request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::ACK, 0};
    std::string request;

    request.reserve(sizeof(Header));
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    _socket->write(request);
    _status = status::ACK;
}

void Client::sendMessageReq()
{
    //TODO:

}

void Client::sendCancelReq()
{
    //TODO:
    std::cout << "{CLIENT} send cancel request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::CANCEL, 0};
    std::string request;

    request.reserve(sizeof(Header));
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    stopAudioAndUDP();
    _socket->write(request);
    _status = status::CANCEL;
}

void Client::sendByeReq()
{
    /*
    * 1 - Eteindre l'audio et l'udp
    */
    std::cout << "{CLIENT} send bye request" << std::endl;

    if (!_socket->isConnected()) {
        return reconnectClient();
    }

    stopAudioAndUDP();
    Header header = {request::BYE, 0};
    std::string request;

    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    _socket->write(request);
    _status = status::BYE;
    _graphical->setScene("Home");
}

void Client::sendRegisterReq(const std::string &username, const std::string &password)
{
    /*
    * 1 - Envoyer au serveur les donnes
    */
    std::cout << "{CLIENT} send registered request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::REGISTER, 100};
    std::string request;

    std::string userReq(50, 0);
    std::string passReq(50, 0);

    std::copy_n(username.begin(), username.size(), userReq.begin());
    std::copy_n(password.begin(), password.size(), passReq.begin());

    request.reserve(sizeof(Header) + header.messageSize);
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    request.append(userReq.c_str(), 50);
    request.append(passReq.c_str(), 50);
    _socket->write(request);
    _status = status::REGISTER;
}

void Client::sendLoginReq(const std::string &login, const std::string &password)
{
    std::cout << "{CLIENT} send login request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::LOGIN, 100};
    std::string request;

    std::string userReq(50, 0);
    std::string passReq(50, 0);

    std::copy_n(login.begin(), login.size(), userReq.begin());
    std::copy_n(password.begin(), password.size(), passReq.begin());

    request.reserve(100 + sizeof(Header));
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    request.append(userReq.c_str(), 50);
    request.append(passReq.c_str(), 50);
    _socket->write(request);
    _status = status::LOGIN;
}

void Client::sendLogoutReq()
{
    std::cout << "{CLIENT} send logout request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::LOGOUT, 0};
    std::string request;

    request.reserve(sizeof(Header));
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    _socket->write(request);
    _status = status::LOGOUT;
}

void Client::sendContactInfoReq(int id)
{
    //TODO:

    std::cout << "{CLIENT} send contact info request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {request::INFO_CONTACT, sizeof(int)};
    std::string request;

    request.reserve(sizeof(Header) + header.messageSize);
    std::memcpy(request.data(), &header, sizeof(Header));
    std::memcpy(request.data() + sizeof(Header), &id, sizeof(int));
    _socket->write(request);
    _status = status::INFO_CONTACT;
}

void Client::sendRingingReq()
{
    //TODO:

    /*
    * 1 - Récupérer ipv6 et port
    * 2 - Envoyer req
    */
    std::cout << "{CLIENT} send ringing request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    if (_socketUDP == nullptr)
        return;
    short port = static_cast<QTSocketUDP *>(_socketUDP.get())->getPort();

    Header header = {response::RINGING, 2};
    std::string request;

    request.reserve(sizeof(Header) + header.messageSize);
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    request.append(reinterpret_cast<char *>(&port), sizeof(short));
    _socket->write(request);
    _status = status::RINGING;
}

void Client::sendOkReq()
{
    //TODO:

    std::cout << "{CLIENT} send ok request" << std::endl;

    if (!_socket->isConnected())
        return reconnectClient();

    Header header = {response::OK, 0};
    std::string request;

    request.reserve(sizeof(Header) + header.messageSize);
    request.append(reinterpret_cast<char *>(&header), sizeof(Header));
    _socket->write(request);
    _status = status::OK;
}

std::string Client::binaryIPV4ToString(const std::string &adress) const
{
    std::string ipv4Str;

    for (size_t i = 0; i < 4; i++) {
        unsigned char nb;

        if (i != 0)
            ipv4Str += ".";
        nb = static_cast<unsigned char>(adress.c_str()[i]);
        ipv4Str += std::to_string(nb);
    }
    return (ipv4Str);
}

void Client::startAudio()
{
    if (_socketUDP == nullptr)
        return;
    _audioEncoder = std::make_shared<AudioEncoder>(CHANNELS, FRAME_RATE, SAMPLE_RATE);
    userDataPa.audioEncoder = _audioEncoder;
    std::cout << "CLIENT start audio" << std::endl;
    _audio = std::make_unique<Audio>();
    static_cast<Audio *>(_audio.get())->setCallbackFunction(
        [](
            const void *input,
            void *output,
            unsigned long frameCount,
            const PaStreamCallbackTimeInfo *timeInfo,
            PaStreamCallbackFlags statusFlags,
            void *userData
        ) -> int {
            UserData::ScopedLock lock(userDataPa);
            int16_t *ou = (int16_t *)output;
            int16_t *in = (int16_t *)input;

            if (!userDataPa.audioEncoder || !userDataPa.socketUDP)
                return (0);
            auto encodeData = userDataPa.audioEncoder->encode(in);
            userDataPa.socketUDP->write(encodeData, userDataPa.audioEncoder->getDataLength());
            if (userDataPa.datas.size() != 0) {
                int16_t *data = userDataPa.datas.front();
                for (int i = 0; i < CHANNELS * FRAME_RATE; i++) {
                    *ou++ = *data++;
                }
                int16_t *front = userDataPa.datas.front();
                userDataPa.datas.pop();
                delete front;
            }
            return (0);
        });
    _audio->openPort();
    _audio->start();
}

void Client::stopAudio()
{
    if (_audio == nullptr)
        return;
    _audio.reset();
    _audio = nullptr;
    if (_audioEncoder == nullptr)
        return;
    _audioEncoder.reset();
    _audioEncoder = nullptr;
    userDataPa.audioEncoder = nullptr;
}

void Client::stopUDP()
{
    if (_socketUDP == nullptr)
        return;
    _socketUDP.reset();
    _socketUDP = nullptr;
    userDataPa.socketUDP = nullptr;
}

void Client::startSocketUDP()
{
    std::cout << "CLIENT start UDP" << std::endl;
    _socketUDP = std::make_shared<QTSocketUDP>(44000);
    _socketUDP->setReadFct([this](const std::string &data) -> int {
        static int i = 0;
        if (!_audioEncoder)
            return (0);
        try {
            UserData::ScopedLock lock(userDataPa);
            int16_t *dataDecode = _audioEncoder->decode(data, data.length());
            i++;
            userDataPa.size = data.length();
            userDataPa.datas.push(dataDecode);
        } catch(std::exception& e) {
            std::cerr << e.what() << '\n';
        }
        return (0);
    });
    userDataPa.socketUDP = _socketUDP;
}

void Client::reconnectClient()
{
    stopAudioAndUDP();
    _graphical->setScene("Connexion");
    static_cast<QTSocketTCP *>(_socket.get())->connectHost();
    DialogBox badRequest("Bad Request", "Connexion to server lost", DialogBox::Dlevel::CRITICAL);
}

void Client::stopAudioAndUDP()
{
    stopAudio();
    stopUDP();
}
