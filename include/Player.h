#pragma once

//#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

#include "Projectile.h"

using namespace std;

class Player: public Animation
{
    protected:
        Projectile projectile;
        vector<Projectile> vectProj;

    public:
        //ctor dtor
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed);
        virtual ~Player();

        //sets
        void setSpeed(float _speed);
        void setBodyPosition(float x, float y);

        //gets
        sf::RectangleShape getBody();
        sf::Vector2f GetPosition();
        bool getFaceRight();

        //interacoes com o ambiente
        //do personagem
        void CheckActivePlatform(Platform &platform);
        void StaticCheckCollision(Platform &platform);
        void MovableCheckCollision(Platform &platform, float mass);
        //do tiro
        void Projectile_CheckCollision(sf::RectangleShape target);
        void Projectile_CheckCollision_Damage(sf::RectangleShape target, float &damage);


        //Atualizacao e grafico personagem
        void Update_Player(float deltaTime); //QUERO QUE SEJA "OVERRIDEN"
        void Draw(sf::RenderWindow& window);


        //Atualizacao e grafico tiro
        void Projectile_Update(float deltaTime);
        void Projectile_Draw(sf::RenderWindow& window);

    public:
        float damage;

    protected:
        unsigned int i;
        sf::RectangleShape body;
        unsigned int row;
        float speed;
        bool faceRight;
        bool hitTheFloor;
        sf::Vector2f velocity;
        float jumpHeight;

        //CD == cooldown
        float shootCD;
        float jumpCD;

        //usado nos enemies
        bool hitTheWall;
};

