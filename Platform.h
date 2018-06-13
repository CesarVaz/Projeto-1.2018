#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
    public:
        Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

        void Draw(sf::RenderWindow& window);

        sf::RectangleShape getBody();

        void bodyMove(float moveX, float moveY);
        void setBodyPosition(float x, float y);

    protected:
        sf::RectangleShape body;
};
