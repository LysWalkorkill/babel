/*
** EPITECH PROJECT, 2020
** babel_client
** File description:
** TODO: add description
*/

#ifndef BABEL_AWIDGETS_HPP
#define BABEL_AWIDGETS_HPP

#include "IWidgets.hpp"

namespace babel::graphical
{
    class AWidgets : public IWidgets {
        public:
            explicit AWidgets(int id);
            ~AWidgets();

            void setID(int id) override;
            [[nodiscard]] int getID() const override;

        private:
            int _id;
    };
}

#endif //BABEL_IWidgets_HPP
