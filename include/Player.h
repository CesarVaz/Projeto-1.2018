#pragma once

#include <iostream>
#include <math.h>
#include <vector>

#include "Projectile.h"

using namespace std;

class Player: public Animation
{
    public:
        //ctor dtor
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed);

        //sets
        void setSpeed(float _speed);
        void setBodyPosition(float x, float y);

        //gets
        sf::RectangleShape getBody();
        sf::Vector2f GetPosition();
        bool getFaceRight();
        bool getDead();

        //interacoes com o ambiente
        //do personagem
        void CheckCollision_Player(sf::RectangleShape otherBody);
        //do tiro
        void CheckCollision_ProjectileVector(sf::RectangleShape target);
        void CheckCollision_ProjectileVector_Damage(sf::RectangleShape target, float &damage);

        //INPUTS
        void move(string direction);
        void jump();
        void shoot();

        //Atualizacao e grafico personagem
        void Update_Player(float deltaTime);
        void Draw_Player(sf::RenderWindow& window);

        //Atualizacao e grafico tiro
        void Update_ProjectileVector(float deltaTime);
        void Draw_ProjectileVector(sf::RenderWindow& window);

    public:
        float damage;

    protected:
        Projectile projectile;
        vector<Projectile> vectProj;

        unsigned int i;
        sf::RectangleShape body;
        unsigned int row;
        float speed;
        bool faceRight;
        sf::Vector2f velocity;
        float jumpHeight;
        bool dead;
        bool hitTheFloor;

        //CD == cooldown
        float shootCD;
        float jumpCD;

        //ULTIMA PLATAFORMA COLIDIDA
        sf::FloatRect globalBounds;

};

