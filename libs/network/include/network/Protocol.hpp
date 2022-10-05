/*
** EPITECH PROJECT, 2020
** B-CPP-500-NAN-5-1-babel-jamil.ettel
** File description:
** Protocol
*/

#ifndef PROTOCOL_HPP_
#define PROTOCOL_HPP_

#define MAX_INPUT_SIZE 50
#define MAX_MESSAGE_SIZE 512

#ifdef __GNUC__
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK(__Declaration__) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

namespace babel::network
{
    PACK(struct Header
    {
        unsigned short nb;
        int messageSize;
    });

    namespace response {
        enum Response
        {
            TRY = 100,
            RINGING = 180,
            OK = 200,
            USER_REGISTERED = 220,
            USER_LOGGED_IN = 221,
            USER_LOGGED_OUT = 222,
            CONTACTS = 240,
            INFO_CONTACT = 241,
            BAD_REQUEST = 400,
            UNAUTHORIZED = 401,
            NOT_FOUND = 404,
            INTERNAL_ERROR = 500,
            UNAVAILABLE = 503
        };
    }

    namespace request {
        enum Request
        {
            INVITE = 1,
            ACK = 2,
            MESSAGE = 3,
            CANCEL = 10,
            BYE = 15,
            REGISTER = 20,
            LOGIN = 21,
            LOGOUT = 22,
            CONTACTS = 30,
            NOTIFY_CONTACT = 31,
            INFO_CONTACT = 32
        };
    }

} // namespace babel::network


#endif /* !PROTOCOL_HPP_ */
