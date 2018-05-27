#pragma once

#include <SFML/Graphics.hpp>

class Rect_Teste
{
    public:
        Rect_Teste();
        virtual ~Rect_Teste();


        void Draw(sf::RenderWindow& window);
        void setBodyPosition(sf::Vector2f playerPos, bool faceRight);
        void setToDelete(bool toDelete);
        void StaticCheckCollision(sf::RectangleShape target);

        sf::Vector2f getBodyPos();

        float duration;
        float totalTime;

    protected:

    private:
            sf::RectangleShape body;
            sf::Vector2f iniPosition;
            bool toDelete;

};

