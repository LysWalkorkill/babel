/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#include "graphical/AWidgets.hpp"

using namespace babel::graphical;

AWidgets::AWidgets(int id) : _id(id)
{
}

AWidgets::~AWidgets()
= default;

void AWidgets::setID(int id)
{
    _id = id;
}

int AWidgets::getID() const
{
    return _id;
}
