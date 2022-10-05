/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#include "graphical/DialogBox.hpp"

using namespace babel::graphical;

DialogBox::DialogBox(const std::string &title, const std::string &text, const DialogBox::Dlevel &lvl, QWidget *NWindow) : _id(-1), _question(true) {
    switch (lvl) {
    case Dlevel::INFORMATION:
        QMessageBox::information(NWindow, QString::fromStdString(title), QString::fromStdString(text));
        break;
    case Dlevel::WARNING:
        QMessageBox::information(NWindow, QString::fromStdString(title), QString::fromStdString(text));
        break;
    case Dlevel::CRITICAL:
        QMessageBox::information(NWindow, QString::fromStdString(title), QString::fromStdString(text));
        break;
    case Dlevel::QUESTION:
        this->Question(*NWindow, title, text);
        break;
    case Dlevel::TEXT:
        this->Text(*NWindow, title, text);
        break;
    default:
        break;
    }
}

DialogBox::~DialogBox() = default;

void DialogBox::Question(QWidget &NWindow, const std::string &title, const std::string &text) {
    int reponse = QMessageBox::information(&NWindow, QString::fromStdString(title), QString::fromStdString(text), QMessageBox::Yes | QMessageBox::No);
    if (reponse == QMessageBox::Yes)
        this->_question = true;
    else
        this->_question = false;
}

void DialogBox::Text(QWidget &NWindow, const std::string &title, const std::string &text) {
    QString txt = QInputDialog::getText(&NWindow, QString::fromStdString(title), QString::fromStdString(text));
    this->_text = txt.toStdString();
}

bool DialogBox::getQuestion() const
{
    return this->_question;
}

const std::string &DialogBox::getText() const
{
    return this->_text;
}

void DialogBox::setID(int id)
{
    _id = id;
}

int DialogBox::getID() const
{
    return _id;
}
