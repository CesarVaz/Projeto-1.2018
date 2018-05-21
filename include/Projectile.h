#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Player.h"

class Projectile
{
    public:
        Projectile(Player player);
        virtual ~Projectile();

        void Draw(sf::RenderWindow& window);

        sf::Vector2f GetPosition();

        void setSpeed(float _speed);

        void setBodyPosition(sf::Vector2f playerPos, bool faceRight);

        sf::RectangleShape getBody();

            void Update(float deltaTime);

            void StaticCheckCollision(Platform &platform);

            void setIsAvailable(bool available);

            bool getIsAvailable();

            bool setFaceRight(bool faceRight);

    protected:

    private:
        sf::RectangleShape body;
        float speed, def_Speed;
        bool faceRight;
        sf::Vector2f velocity;
        bool isAvailable;
        sf::Vector2f iniPosition;


};
