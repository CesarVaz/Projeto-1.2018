#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Platform.h"
#include <math.h>
#include <iostream>
#include "Projectile.h"

#include "Rect_Teste.h"
#include <vector>

using namespace std;


class Player
{
    private:
        Animation animation;

    public:
        Projectile projectile;
        vector<Rect_Teste> t1;

    public:
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Texture* projTexture);
        virtual ~Player();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow& window);

            sf::Vector2f GetPosition();

            void setSpeed(float _speed);

            void setBodyPosition(float x, float y);

            sf::RectangleShape getBody();

            void CheckActivePlatform(Platform &platform);
            void StaticCheckCollision(Platform &platform);
            void MovableCheckCollision(Platform &platform, float mass);

            bool getFaceRight();



    private:
        sf::RectangleShape body;
        unsigned int row;
        float speed, def_Speed;
        bool faceRight;
        bool hitTheFloor;
        sf::Vector2f velocity;
        float jumpHeight;
        sf::Vector2f collisionDirection; //sem uso
        sf::Vector2f projVelocity;
        float shootCD;
        float jumpCD;

};

