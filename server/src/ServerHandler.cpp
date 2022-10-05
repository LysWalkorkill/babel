/*
** EPITECH PROJECT, 2020
** Babel
** File description:
** ServerHandler
*/

#include "server/ServerHandler.hpp"
#include "network/Protocol.hpp"
#include "server/ClientInfo.hpp"
#include "server/Storage.hpp"

using namespace babel::server;
using namespace babel::network;

ServerHandler::ServerHandler(int port):
    _server(port),
    _dbHandler(DBHandler("db.sqlite")),
    _userHandler(_dbHandler)
{
    _server.setAcceptHandler([this] (boost::shared_ptr<network::ISocket> &connection) {
        return this->handleAccept(connection);
    });
}

void ServerHandler::run()
{
    _server.acceptClient();
    _server.run();
}

std::string ServerHandler::prepareHeader(unsigned short code, int size)
{
    std::string response;
    network::Header header = {code, size};

    response.reserve(size + sizeof(Header));
    response.append(reinterpret_cast<char *>(&header), sizeof(Header));

    return response;
}

bool ServerHandler::handleAccept(boost::shared_ptr<network::ISocket> &connection)
{
    std::cout << "{SERVER} New connection" << std::endl;
    auto &client = _clients.emplace_back(new ClientInfo(connection));
    auto ptr = client.get();

    connection->setWriteFct([this, ptr] () {this->writeHandler(*ptr);});
    connection->setReadFct([this, ptr] (const std::string &str) {return this->readHandler(*ptr, str);});
    connection->setDisconnectFct([this, ptr] () {this->disconnectHandler(*ptr);});

    std::string response = prepareHeader(network::response::OK, 0);

    connection->write(response);

    return true;
}

void ServerHandler::writeHandler(ClientInfo &clientInfo)
{
    if (!clientInfo.isReading) {
        clientInfo.socket->read();
        clientInfo.isReading = true;
    }
}

int ServerHandler::readHandler(ClientInfo &clientInfo, const std::string &str)
{
    std::cout << "{SERVER} Enter to readHandler" << std::endl;
    network::Header header = {0, 0};

    if (str.length() < sizeof(Header)) {
        // std::cout << "NOP" << std::endl;
        clientInfo.socket->read();
        clientInfo.isReading = true;
        return 0;
    }
    std::memcpy(&header, str.c_str(), sizeof(Header));
    if (str.length() < sizeof(Header) + header.messageSize) {
        // std::cout << "NOPpppppp" << std::endl;
        clientInfo.socket->read();
        clientInfo.isReading = true;
        return 0;
    }

    clientInfo.isReading = false;
    std::string message;
    message.reserve(header.messageSize);
    message.append(str.c_str() + sizeof(Header), header.messageSize);

    auto fct = eventsHandlers.find(header.nb);
    if (fct != eventsHandlers.end())
        (this->*fct->second)(clientInfo, message);
    else
        this->unknownEvt(clientInfo, message);

    return sizeof(Header) + header.messageSize;
}

void ServerHandler::disconnectHandler(ClientInfo &clientInfo)
{
    auto it = std::find_if(
        _clients.begin(), _clients.end(),
        [&clientInfo] (const boost::shared_ptr<ClientInfo> &elem) {
            return &clientInfo == elem.get();
        });
    if (it == _clients.end())
        return;

    if (clientInfo.user.has_value() && clientInfo.otherUser != -1) {
        auto client = getClient(clientInfo.otherUser);
        if (client && client->status != ClientInfo::CLOSING_CALL) {
            client->status = ClientInfo::CLOSING_CALL;
            if (client->status == ClientInfo::IN_CALL)
                client->socket->write(prepareHeader(request::BYE, 0));
            else
                client->socket->write(prepareHeader(request::CANCEL, 0));
        }
    }
    if (it->get()->user.has_value())
        _userHandler.disconnectUser(it->get()->user->id);
    _clients.erase(it);
    sendContacts();
}

const std::map<unsigned short, void (ServerHandler::*)(ClientInfo &client, const std::string &message)>
ServerHandler::eventsHandlers = {
    {request::BYE, &ServerHandler::byeEvt},
    {request::CANCEL, &ServerHandler::cancelEvt},
    {request::INVITE, &ServerHandler::inviteEvt},
    {request::ACK, &ServerHandler::ackEvt},
    {request::REGISTER, &ServerHandler::registerEvt},
    {request::LOGIN, &ServerHandler::loginEvt},
    {request::LOGOUT, &ServerHandler::logoutEvt},
    {request::CONTACTS, &ServerHandler::contactsEvt},
    {request::INFO_CONTACT, &ServerHandler::infoEvt},
    {response::RINGING, &ServerHandler::ringingEvt},
    {response::OK, &ServerHandler::okEvt},
};

void ServerHandler::byeEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Enter to bye evt" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 0 || client.status != ClientInfo::IN_CALL) {
        std::cout << "{SERVER} bye evt: bad request" << std::endl;
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));
    }

    auto otherClient = getClient(client.otherUser);
    if (!otherClient) {
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} bye evt: unavailable" << std::endl;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    } else if (otherClient->otherUser != client.user->id || otherClient->status != ClientInfo::IN_CALL) {
        if (otherClient->status != ClientInfo::IN_CALL) {
            otherClient->otherUser = -1;
            otherClient->status = ClientInfo::FREE;
        }
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} bye evt: internal error" << std::endl;
        return client.socket->write(prepareHeader(response::INTERNAL_ERROR, 0));
    }

    otherClient->status = ClientInfo::CLOSING_CALL;
    client.status = ClientInfo::FREE;
    client.otherUser = -1;

    std::cout << "{SERVER} bye evt: ok and bye" << std::endl;
    client.socket->write(prepareHeader(response::OK, 0));
    otherClient->socket->write(prepareHeader(request::BYE, 0));
}

void ServerHandler::cancelEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Enter to cancel evt" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 0 || client.status == ClientInfo::IN_CALL || client.status == ClientInfo::FREE)
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));

    auto otherClient = getClient(client.otherUser);
    if (!otherClient) {
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    } else if (otherClient->otherUser != client.user->id || otherClient->status == ClientInfo::IN_CALL || otherClient->status == ClientInfo::FREE) {
        if (otherClient->status != ClientInfo::IN_CALL) {
            otherClient->otherUser = -1;
            otherClient->status = ClientInfo::FREE;
        }
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        return client.socket->write(prepareHeader(response::INTERNAL_ERROR, 0));
    }

    client.status = ClientInfo::FREE;
    client.otherUser = -1;

    client.socket->write(prepareHeader(response::OK, 0));

    otherClient->status = ClientInfo::CLOSING_CALL;
    otherClient->socket->write(prepareHeader(request::CANCEL, 0));
}

void ServerHandler::inviteEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Enter to invite evt" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 6 || client.status != ClientInfo::FREE) {
        std::cout << "{SERVER} Bad request : Message size is not 6 or client status is not set to FREE" << std::endl;
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));
    }

    int id = 0;
    short port = 0;

    id = *reinterpret_cast<const int *>(message.c_str());
    port = *reinterpret_cast<const short *>(message.c_str() + sizeof(int));

    if (id == client.user->id) {
        std::cout << "{SERVER} Bad request : Client try to call himself" << std::endl;
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));
    }

    auto otherClient = getClient(id);

    if (otherClient == nullptr) {
        std::cout << "{SERVER} Not found" << std::endl;
        return client.socket->write(prepareHeader(response::NOT_FOUND, 0));
    } else if (otherClient->status != ClientInfo::FREE) {
        std::cout << "{SERVER} Unavailable" << std::endl;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    }

    client.otherUser = otherClient->user->id;
    otherClient->otherUser = client.user->id;

    auto ip = client.socket->getIp();
    std::string invite = prepareHeader(request::INVITE, sizeof(int) + 4 + sizeof(short));

    invite.append(reinterpret_cast<char *>(&client.user->id), sizeof(int));
    invite.append(reinterpret_cast<char *>(ip.data()), 4);
    invite.append(reinterpret_cast<char *>(&port), sizeof(short));
    otherClient->socket->write(invite);

    client.socket->write(prepareHeader(response::TRY, 0));

    client.status = ClientInfo::TRYING;
    otherClient->status = ClientInfo::INVITING;
}

void ServerHandler::ringingEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Enter to ringing evt" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 2 || client.status != ClientInfo::INVITING)
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));

    auto otherClient = getClient(client.otherUser);
    if (!otherClient) {
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} Ringing evt : unavailable" << std::endl;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    } else if (otherClient->otherUser != client.user->id || otherClient->status != ClientInfo::TRYING) {
        if (otherClient->status != ClientInfo::TRYING) {
            otherClient->otherUser = -1;
            otherClient->status = ClientInfo::FREE;
        }
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} Ringing evt : internal error" << std::endl;
        return client.socket->write(prepareHeader(response::INTERNAL_ERROR, 0));
    }

    std::cout << "{SERVER} Ringing evt : read and write ringing" << std::endl;

    short port = *reinterpret_cast<const short *>(message.c_str());
    auto ip = client.socket->getIp();

    std::string ringingMsg = prepareHeader(response::RINGING, 4 + sizeof(short));
    ringingMsg.append(reinterpret_cast<char *>(ip.data()), 4);
    ringingMsg.append(reinterpret_cast<char *>(&port), sizeof(short));
    otherClient->socket->write(ringingMsg);

    client.status = ClientInfo::RINGING;
    otherClient->status = ClientInfo::WAITING;
    
    if (!client.isReading) {
        client.socket->read();
        client.isReading = true;
    }
}

void ServerHandler::okEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} enter to ok event" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 0)
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));
    if (client.status != ClientInfo::RINGING) {
        if (client.status == ClientInfo::CLOSING_CALL) {
            client.otherUser = -1;
            client.status = ClientInfo::FREE;
            std::cout << "{SERVER} ok event: Closing all" << std::endl;
            return client.socket->read();
        }
        std::cout << "{SERVER} ok event: bad request" << std::endl;
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));
    }

    auto otherClient = getClient(client.otherUser);
    if (!otherClient) {
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} ok event: unavailable" << std::endl;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    } else if (otherClient->otherUser != client.user->id || otherClient->status != ClientInfo::WAITING) {
        if (otherClient->status != ClientInfo::WAITING) {
            otherClient->otherUser = -1;
            otherClient->status = ClientInfo::FREE;
        }
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        std::cout << "{SERVER} ok event : internal error" << std::endl;
        return client.socket->write(prepareHeader(response::INTERNAL_ERROR, 0));
    }

    client.socket->write(prepareHeader(request::ACK, 0));
    client.status = ClientInfo::IN_CALL;

    otherClient->socket->write(prepareHeader(response::OK, 0));
    otherClient->status = ClientInfo::WAITING_ACK;
}

void ServerHandler::ackEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Enter to ack evt" << std::endl;
    if (!client.user.has_value())
        return client.socket->write(prepareHeader(response::UNAUTHORIZED, 0));
    if (message.size() != 0 || client.status != ClientInfo::WAITING_ACK)
        return client.socket->write(prepareHeader(response::BAD_REQUEST, 0));

    auto otherClient = getClient(client.otherUser);
    if (!otherClient) {
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        return client.socket->write(prepareHeader(response::UNAVAILABLE, 0));
    } else if (otherClient->otherUser != client.user->id || otherClient->status != ClientInfo::IN_CALL) {
        if (otherClient->status != ClientInfo::IN_CALL) {
            otherClient->otherUser = -1;
            otherClient->status = ClientInfo::FREE;
        }
        client.otherUser = -1;
        client.status = ClientInfo::FREE;
        return client.socket->write(prepareHeader(response::INTERNAL_ERROR, 0));
    }

    client.status = ClientInfo::IN_CALL;
    otherClient->status = ClientInfo::IN_CALL;

    // read is usually only called after a write, but no write is occuring in this function
    client.socket->read();
}

void ServerHandler::registerEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Register event" << std::endl;
    std::string username(50, 0);
    std::string password(50, 0);

    if (message.size() != 100) {
        std::string response = prepareHeader(response::BAD_REQUEST, 0);
        client.socket->write(response);
        std::cout << "here1" << std::endl;
        std::cout << "{SERVER} Bad request" << std::endl;
        return;
    }
    std::copy_n(message.begin(), 50, username.begin());
    std::copy_n(message.begin() + 50, 50, password.begin());

    if (username[0] == 0 || password[0] == 0) {
        std::string response = prepareHeader(response::BAD_REQUEST, 0);
        client.socket->write(response);
        std::cout << "here2" << std::endl;
        std::cout << "{SERVER} Bad Request" << std::endl;
        return;
    }

    int id = _userHandler.insertUser({-1, username, password, true});
    if (id == -1) {
        std::string response = prepareHeader(response::BAD_REQUEST, 0);
        client.socket->write(response);
        std::cout << "here3" << std::endl;
        std::cout << "{SERVER} Bad Request" << std::endl;
    } else {
        std::string response = prepareHeader(response::USER_REGISTERED, 50);
        response.append(username.c_str(), 50);
        client.user.emplace(User{id, username, password, true});
        client.socket->write(response);
        sendContacts();
    }
}

void ServerHandler::loginEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Login event" << std::endl;
    std::string username(50, 0);
    std::string password(50, 0);

    if (message.size() < 100) {
        std::string response = prepareHeader(response::BAD_REQUEST, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Bad request" << std::endl;
        return;
    }
    std::copy_n(message.begin(), 50, username.begin());
    std::copy_n(message.begin() + 50, 50, password.begin());

    int id = _userHandler.connectUser(username, password);
    if (id == -1) {
        std::string response = prepareHeader(response::NOT_FOUND, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Not found" << std::endl;
    } else {
        std::string response = prepareHeader(response::USER_LOGGED_IN, 50);
        response.append(username.c_str(), 50);
        client.user.emplace(User{id, username, password});
        client.socket->write(response);
        sendContacts();
    }
}

void ServerHandler::logoutEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Logout event" << std::endl;

    if (client.user.has_value()) {
        _userHandler.disconnectUser(client.user.value().id);
        std::string response = prepareHeader(response::USER_LOGGED_OUT, 0);
        client.user.reset();
        client.socket->write(response);
        sendContacts();
    } else {
        std::string response = prepareHeader(response::BAD_REQUEST, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Bad request" << std::endl;
    }
}

void ServerHandler::contactsEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Contacts event" << std::endl;
    if (!client.user.has_value()) {
        std::string response = prepareHeader(response::UNAUTHORIZED, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Unauthorized" << std::endl;
        return;
    }
    sendContacts();
}

void ServerHandler::infoEvt(ClientInfo &client, const std::string &message)
{
    std::cout << "{SERVER} Contact info event" << std::endl;

    if (!client.user.has_value()) {
        std::string response = prepareHeader(response::UNAUTHORIZED, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Unauthoried" << std::endl;
        return;
    }

    int id;

    std::memcpy(&id, message.c_str(), sizeof(int));
    User user = _userHandler.getUser(id);
    if (user.id == -1) {
        std::string response = prepareHeader(response::NOT_FOUND, 0);
        client.socket->write(response);
        std::cout << "{SERVER} Not found" << std::endl;
    } else {
        std::string response = prepareHeader(response::INFO_CONTACT, 55);
        int id = user.id;
        bool status = true;
        response.append(reinterpret_cast<char *>(id), sizeof(int));
        response.append(reinterpret_cast<char *>(status), 1);
        response.append(user.username.c_str(), 50);
        client.socket->write(response);
    }
}

void ServerHandler::unknownEvt(ClientInfo &client, const std::string &)
{
    std::string response = prepareHeader(response::NOT_FOUND, 0);
    client.socket->write(response);
}

void ServerHandler::sendContactNotify(const User &user, bool status) const
{
    std::for_each(_clients.begin(), _clients.end(), [this, &user, &status](const boost::shared_ptr<ClientInfo> &client) {
        if (!client->user.has_value() || client->user.value().id == user.id)
            return;
        std::string response = prepareHeader(request::NOTIFY_CONTACT, 55);
        int id = user.id;
        response.append(reinterpret_cast<char *>(&id), sizeof(int));
        response.append(reinterpret_cast<char *>(&status), 1);
        response.append(user.username.c_str(), 50);
        client->socket->write(response);
    });
}

boost::shared_ptr<ClientInfo> ServerHandler::getClient(int userId) const
{
    auto it = std::find_if(
        _clients.begin(), _clients.end(),
        [userId] (const boost::shared_ptr<ClientInfo> &client2) {
            return client2->user.has_value() && userId == client2->user->id;
        });

    if (it == _clients.end())
        return nullptr;
    return *it;
}

void ServerHandler::sendContacts() const
{
    std::vector<User> users = _userHandler.getUsers();

    std::for_each(_clients.begin(), _clients.end(), [this, &users](const boost::shared_ptr<ClientInfo> &client) {
        if (!client->user.has_value())
            return;
        std::string response = prepareHeader(response::CONTACTS, (users.size() - 1) * 55);
        for (const auto &user : users) {
            if (client->user->id == user.id)
                continue;
            int id = user.id;
            bool status = user.connected;
            response.append(reinterpret_cast<char *>(&id), sizeof(int));
            response.append(reinterpret_cast<char *>(&status), 1);
            response.append(user.username.c_str(), 50);
        }
        client->socket->write(response);
    });
}
