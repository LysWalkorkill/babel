/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef BABEL_IWIDGETS_HPP
#define BABEL_IWIDGETS_HPP

#include <QPushButton>
#include <QObject>
#include <QApplication>
#include <QWidget>

namespace babel::graphical
{
    /*
        interface of all major QWidget : Widget, LineEdit, Label, Qbutton
        all of this classes encaplusate QT Widget -> QWidget
    */
    class IWidgets {
        public:
            /*
                it mostly use for the content of the widget, as text or description
                text for QButton, Label
                descritpion for LineEdit, Widget
            */
            virtual void setText(const std::string&) = 0;
            /*
                encapsulation of QT show method
                it choose if the widget is visible
                it's alway visible if this method isn't call
            */
            virtual void show(bool) = 0;
            /*
                encapsualtion of QT move method
                it place the widget on a window, with x-coordinate and y-coordinate 
            */
            virtual void move(int, int) = 0;
            /*
                encapsualtion of QT Size method
                it change the size of a widget,
                the result may be different widget to widegt, as Label.
            */
            virtual void setSize(int, int) = 0;
            /*
                encapsulation of QT Gemoetry
                it work as move and size, but do both in a time.
            */
            virtual void setGeometry(int, int, int, int) = 0;

            /*
                return X-coordinate
            */
            [[nodiscard]] virtual int getX() const = 0;
            /*
                return Y-coordinate
            */
            [[nodiscard]] virtual int getY() const = 0;
            /*
                return Lenght
            */
            [[nodiscard]] virtual int getLength() const = 0;
            /*
                return Width
            */
            [[nodiscard]] virtual int getWidth() const = 0;
            /*
                return the actual widget
            */
            [[nodiscard]] virtual QWidget* getWidgets() const = 0;

            /*
                encaplustion of QT setStyleSheet
                it customize the Foreground and Background Colors
            */
            virtual void setStyleSheet(const std::string &style) = 0;
            virtual void setObjectName(const std::string &name) = 0;

            /*
                it set the ID of the widget
                it allows to find the widget in a scene 
            */
            virtual void setID(int id) = 0;
            /*
                return the widget ID
            */
            [[nodiscard]] virtual int getID() const = 0;

    private:
    };
}

#endif //BABEL_IWidgets_HPP
