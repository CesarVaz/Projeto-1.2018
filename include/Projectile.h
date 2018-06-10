#pragma once

#include "Platform.h"
#include "Animation.h"

class Projectile: public Animation
{
    public:
        //ctor dtor
        Projectile(sf::Texture* projTexture);

        //sets
        void setBodyPosition(sf::Vector2f playerPos, bool faceRight);
        void setFaceRight(bool faceRight);
        void addVelocity(sf::Vector2f velocity);

        //gets
        sf::RectangleShape getBody();

        //interacoes com o ambiente
        void CheckCollision(sf::RectangleShape target);
        void CheckCollision_Damage(sf::RectangleShape target, float &damage);

        //Atualizacao e grafico tiro
        void Update_Projectile(float deltaTime);
        void Draw(sf::RenderWindow& window);

        //usados em Projectile.cpp e Player.cpp
        bool collision;
        float duration;
        float totalTime;

    private:
        sf::RectangleShape body;
        float speed;
        bool faceRight;
        sf::Vector2f velocity;
        sf::Vector2f iniPosition;

        //sem uso
        float def_Speed;
};
