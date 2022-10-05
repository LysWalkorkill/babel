/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef BABEL_DIALOG_BOX_HPP
#define BABEL_DIALOG_BOX_HPP

#include <QPushButton>
#include <QObject>
#include <QApplication>
#include <QMessageBox>
#include <QInputDialog>

namespace babel::graphical
{
    class DialogBox {

        public:
            /*
                this enum is used to define the icon type
                INFORMATION, WARNING, CRITICAL only change the icon
                QUESTION allows a yes/no response
                TEXT allows to get text form the user
            */
            enum Dlevel {
                    INFORMATION = 0,
                    WARNING = 1,
                    CRITICAL = 2,
                    QUESTION = 3,
                    TEXT = 4
                };

            /*
                constructor of DialogBox
                the first srting is the name (top left corner of the DialogBox)
                the second string is the text (in the midle of the DialogBox)
                DialogBox::Dlevel define the DialogBox type
                NWindow is the window reference
            */
            DialogBox(const std::string&, const std::string&, const DialogBox::Dlevel&, QWidget *NWindow = nullptr);
            ~DialogBox(); 
            
            /*
                is use to get the response from a QUESTION DiablogBox type
            */
            void Question(QWidget&, const std::string&, const std::string&);
            /*
                is use to get the text from a TEXT DialogBox type
            */
            void Text(QWidget&, const std::string&, const std::string&);
            
            /*
                return true or false from a QUESTION DialogBox type
            */
            bool getQuestion() const;
            /*
                return the text from a TEXT DialogBox Type
            */
            const std::string &getText() const;

            /*
                it set the ID of the DialogBox
                it allows to find the DialogBox in a scene 
            */
            void setID(int id);
            /*
                return the widget ID
            */
            int getID() const;

        private:
            int _id;
            std::string _text;
            bool _question;
    };
}

#endif //BABEL_Dialog_Box_HPP
