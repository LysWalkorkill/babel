/*
** EPITECH PROJECT, 2020
** babel_server
** File description:
** TODO: add description
*/

#ifndef SCENE_HPP
#define SCENE_HPP

#include "IScene.hpp"
#include <string>
#include <utility>
#include <memory>
#include <QtWidgets/QGraphicsScene>

#include "graphical/LineEdit.hpp"
#include "graphical/DialogBox.hpp"

namespace babel::graphical::scene
{
    class Scene : public IScene {
        public:
            explicit Scene(std::string name, int width, int height);
            ~Scene() override;
            Scene(const Scene &) = delete;
            Scene &operator=(const Scene &) = delete;

            [[nodiscard]] const std::string &getName() const override;
            [[nodiscard]] QGraphicsScene &getScene() const;

            void setBackgroundColor(int r, int g, int b, int a) override;

            std::shared_ptr<IWidgets> getWidgetByID(int id) const override;

            void addWidget(const std::shared_ptr<IWidgets>& widget);
            void addMainWidget(const std::shared_ptr<IWidgets>& widget);
            std::shared_ptr<IWidgets> getMainWidget() const;

    private:
            const std::string _name;
            QGraphicsScene *_scene;
            std::vector<std::shared_ptr<IWidgets>> _widgets;
            std::shared_ptr<IWidgets> _mainWidget;
    };
}

#endif //SCENE_HPP
