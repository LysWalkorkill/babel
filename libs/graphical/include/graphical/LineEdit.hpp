/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef BABEL_LINE_EDIT_HPP
#define BABEL_LINE_EDIT_HPP

#include <QPushButton>
#include <QObject>
#include <QApplication>
#include <QLineEdit>
#include "AWidgets.hpp"

namespace babel::graphical
{
    /*
        this classes encapsulate QLineEdit
    */
    class LineEdit: public AWidgets {
        public:
            /*
                constructor 
                QWidget is the window (Widget) this Widget is on
            */
            explicit LineEdit(QWidget&);
            /*
                constructor copy
                it take a LineEdit to copy him
            */
            LineEdit(LineEdit&);
            /*
                constructor
                string is the text inside the Qbutton
                QWidget is the window (Widget) this Widget is on
            */
            LineEdit(const std::string&, QWidget&);
            ~LineEdit();

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
            int getX() const override;
            /*
                return Y-coordinate
            */
            int getY() const override;
            /*
                return Lenght
            */
            int getLength() const override;
            /*
                return Width
            */
            int getWidth() const override;
            /*
                return the actual widget
            */
            QWidget* getWidgets() const override;

            /*
                encaplustion of QT setStyleSheet
                it customize the Foreground and Background Colors
            */
            void setStyleSheet(const std::string &style) override;
            void setObjectName(const std::string &name) override;

            /*
                return what as been write in tht LineEdit
            */
            std::string getTxt();
            /*
                return the description of the LineEdit
            */
            std::string getDescription();

            void setPlaceholder(const std::string &placeholder);
            void setPlaceholderColor(const QColor& color);

            void setHiddenText(bool hide);
            void setMaxLength(int length);

        private:
            QLineEdit *_txt;
            std::string _description;
            int _x;
            int _y;
            int _length;
            int _width;
    };
}

#endif //BABEL_Line_edit_HPP
