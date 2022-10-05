/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#include "graphical/LineEdit.hpp"

using namespace babel::graphical;

LineEdit::LineEdit(QWidget &NWindow) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_txt = new QLineEdit(&NWindow);
}

LineEdit::LineEdit(LineEdit &txt) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_txt = qobject_cast<QLineEdit*>(txt.getWidgets());
}

LineEdit::LineEdit(const std::string &text, QWidget &NWindow) : AWidgets(-1), _x(0), _y(0), _length(0), _width(0) {
    this->_description = text;
    this->_txt = new QLineEdit(&NWindow);
}

LineEdit::~LineEdit() = default;

std::string LineEdit::getTxt() {
    return this->_txt->text().toStdString();
}

std::string LineEdit::getDescription() {
    return this->_description;
}

void LineEdit::setText(const std::string &text) {
    QString qstr = QString::fromStdString(text);
    this->_txt->setText(qstr);
}

void LineEdit::show(bool show) {
    if (show)
        this->_txt->show();
    else
        this->_txt->hide();
}

void LineEdit::move(int x, int y) {
    this->_txt->move(x, y);
    this->_x = x;
    this->_y = y;
}

void LineEdit::setSize(int length, int width) {
    this->_txt->resize(length, width);
    this->_length = length;
    this->_width = width;
}

void LineEdit::setGeometry(int x, int y, int length, int width) {
    this->_txt->setGeometry(this->_x, this->_y, length, width);
    this->_length = length;
    this->_width = width;
    this->_x = x;
    this->_y = y;
}

int LineEdit::getX() const {
    return this->_x;
}

int LineEdit::getY() const {
    return this->_y;
}

int LineEdit::getLength() const {
    return this->_length;
}

int LineEdit::getWidth() const {
    return this->_width;
}

QWidget* LineEdit::getWidgets() const {
    return qobject_cast<QWidget*>(this->_txt);
}

void LineEdit::setStyleSheet(const std::string &style)
{
    _txt->setStyleSheet(style.c_str());
}

void LineEdit::setObjectName(const std::string &name)
{
    _txt->setObjectName(name.c_str());
}

void LineEdit::setPlaceholder(const std::string &placeholder)
{
    _txt->setPlaceholderText(placeholder.c_str());
}

void LineEdit::setPlaceholderColor(const QColor& color)
{
    QPalette p = _txt->palette();
    p.setColor(QPalette::PlaceholderText, color);
    _txt->setPalette(p);
}

void LineEdit::setHiddenText(bool hide)
{
    if (hide)
        _txt->setEchoMode(QLineEdit::Password);
    else
        _txt->setEchoMode(QLineEdit::Normal);
}

void LineEdit::setMaxLength(int length)
{
    _txt->setMaxLength(length);
}
