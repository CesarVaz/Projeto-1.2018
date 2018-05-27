#pragma once
#include <SFML/Graphics.hpp>
#include "Platform.h"

#include "Animation.h"

class Projectile
{
    friend class Player;

    public:
        Projectile(sf::Texture* projTexture);

        Projectile();

        virtual ~Projectile();

        void Draw(sf::RenderWindow& window);

        sf::Vector2f GetPosition();

        void setSpeed(float _speed);

        void setBodyPosition(sf::Vector2f playerPos, bool faceRight);

        sf::RectangleShape getBody();

        void Update(float deltaTime);

        void StaticCheckCollision(sf::RectangleShape target);
        void StaticCheckCollision(sf::RectangleShape target, float &damage);

        void setFaceRight(bool faceRight);

        void setVelocityY(float y);

        void addVelocity(sf::Vector2f velocity);

        bool collision;

        float duration;

        float totalTime;

    protected:

    private:
        sf::RectangleShape body;
        float speed, def_Speed;
        bool faceRight;
        sf::Vector2f velocity;
        sf::Vector2f iniPosition;
        Animation animation;
};
