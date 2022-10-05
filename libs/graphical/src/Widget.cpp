/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#include "graphical/Widget.hpp"

using namespace babel::graphical;

Widget::Widget() : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_widget = new QWidget;
}

Widget::Widget(Widget &widget) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_widget = qobject_cast<QWidget*>(widget.getWidgets());
}

Widget::~Widget() = default;

void Widget::setText(const std::string &text) {
    (void) text;
}

void Widget::show(bool show) {
    if (show)
        this->_widget->show();
    else
        this->_widget->hide();
}

void Widget::move(int x, int y) {
    this->_widget->move(x, y);
    this->_x = x;
    this->_y = y;
}

void Widget::setSize(int length, int width) {
    this->_widget->setFixedSize(length, width);
    this->_length = length;
    this->_width = width;
    _widget->setAttribute( Qt::WA_TranslucentBackground, true );
}

void Widget::setGeometry(int x, int y, int length, int width) {
    this->_widget->setGeometry(this->_x, this->_y, length, width);
    this->_length = length;
    this->_width = width;
    this->_x = x;
    this->_y = y;
}

int Widget::getX() const {
    return this->_x;
}

int Widget::getY() const {
    return this->_y;
}

int Widget::getLength() const {
    return this->_length;
}

int Widget::getWidth() const {
    return this->_width;
}

QWidget* Widget::getWidgets() const {
    return qobject_cast<QWidget*>(this->_widget);
}

void Widget::setStyleSheet(const std::string &style)
{
    _widget->setStyleSheet(style.c_str());
}

void Widget::setObjectName(const std::string &name)
{
    _widget->setObjectName(name.c_str());
}

void Widget::setTransparentBackground(bool transparent)
{
    _widget->setAttribute( Qt::WA_TranslucentBackground, transparent);
}
