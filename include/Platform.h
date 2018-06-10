#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
    public:
        Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

        void Draw_Platform(sf::RenderWindow& window);

        sf::RectangleShape getBody()
        {
            return body;
        }

        void setBodyPosition(float x, float y);

    private:
        sf::RectangleShape body;
};
