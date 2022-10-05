/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef BABEL_QBUTOON_HPP
#define BABEL_QBUTOON_HPP

#include <QPushButton>
#include <QObject>
#include <QApplication>
#include <QIcon>
#include "AWidgets.hpp"

namespace babel::graphical
{
    /*
        this classes encapsulate QPushButton
    */
    class QButton: public AWidgets {
        public:
            /*
                constructor 
                QWidget is the window (Widget) this Widget is on
            */
            explicit QButton(QWidget&);
            /*
                constructor copy
                it take a QButton to copy him
            */
            QButton(QButton&);
            /*
                constructor
                string is the text inside the Qbutton
                QWidget is the window (Widget) this Widget is on
            */
            QButton(const std::string&, QWidget&);
            ~QButton();

            /*
                encapsulation of QT setText method
                string is the text shown on this widget
            */
            void setText(const std::string&) override;
            /*
                encapsulation of QT show method
                it choose if the widget is visible
                it's alway visible if this method isn't call
            */
            void show(bool) override;
            /*
                encapsualtion of QT move method
                it place the widget on a window, with x-coordinate and y-coordinate 
            */
            void move(int, int) override;
            /*
                encapsualtion of QT Size method
                it change the size of a widget,
                the result may be different widget to widegt, as Label.
            */
            void setSize(int, int) override;
            /*
                encapsulation of QT Gemoetry
                it work as move and size, but do both in a time.
            */
            void setGeometry(int, int, int, int) override;

            /*
                return X-coordinate
            */
            [[nodiscard]] int getX() const override;
            /*
                return Y-coordinate
            */
            [[nodiscard]] int getY() const override;
            /*
                return Lenght
            */
            [[nodiscard]] int getLength() const override;
            /*
                return Width
            */
            [[nodiscard]] int getWidth() const override;
            /*
                return the actual widget
            */
            [[nodiscard]] QWidget* getWidgets() const override;

            /*
                encaplustion of QT setStyleSheet
                it customize the Foreground and Background Colors
            */
            void setStyleSheet(const std::string &style) override;
            void setObjectName(const std::string &name) override;

            /*
                ft is a function to use with QT connect
                it will access to ft when the QButton will be pressed
            */
            void connect(std::function<void()> ft);
            /*
                encapsulation of setIcon method
                it place an Icon (jpg/png) to be displayed in this Widget
            */
            void setIcon(const std::string&);
            /*
                it will cancel QButton::connect
            */
            void disconnectAll();

        private:
            QPushButton *_button;
            int _x;
            int _y;
            int _length;
            int _width;
    };
}

#endif //BABEL_QButton_HPP
