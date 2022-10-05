/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#include "graphical/QButton.hpp"
#include <utility>
#include <iostream>

using namespace babel::graphical;

QButton::QButton(QWidget &NWindow) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_button = new QPushButton("sans texte", &NWindow);
}

QButton::QButton(QButton &button) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_button = qobject_cast<QPushButton*>(button.getWidgets());
}

QButton::QButton(const std::string &text, QWidget &NWindow) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    QString qstr = QString::fromStdString(text);
    this->_button = new QPushButton(qstr, &NWindow);
}

QButton::~QButton() = default;

void QButton::setText(const std::string &text) {
    QString qstr = QString::fromStdString(text);
    this->_button->setText(qstr);
}

void QButton::show(bool show) {
    if (show)
        this->_button->show();
    else
        this->_button->hide();
}

void QButton::move(int x, int y) {
    this->_button->move(x, y);
    this->_x = x;
    this->_y = y;
}

void QButton::setSize(int length, int width) {
    this->_button->resize(length, width);
    this->_length = length;
    this->_width = width;
}

void QButton::setGeometry(int x, int y, int length, int width) {
    this->_button->setGeometry(this->_x, this->_y, length, width);
    this->_length = length;
    this->_width = width;
    this->_x = x;
    this->_y = y;
}

int QButton::getX() const {
    return this->_x;
}

int QButton::getY() const {
    return this->_y;
}

int QButton::getLength() const {
    return this->_length;
}

int QButton::getWidth() const {
    return this->_width;
}

QWidget* QButton::getWidgets() const {
    return qobject_cast<QWidget*>(this->_button);
}

void QButton::setStyleSheet(const std::string &style)
{
    _button->setStyleSheet(style.c_str());
}

void QButton::setObjectName(const std::string &name)
{
    _button->setObjectName(name.c_str());
}

void QButton::connect(std::function<void()> ft)
{
    QPushButton::connect(_button, &QPushButton::clicked, std::move(ft));
}

void QButton::setIcon(const std::string& icon) {
    this->_button->setIcon(QIcon(icon.c_str()));
    this->_button->setIconSize(QSize(20, 20));
}
void QButton::disconnectAll()
{
    QPushButton::disconnect(_button, nullptr, nullptr, nullptr);
}
