#pragma once

#include "Player.h"


class Enemy: public Player
{
    public:
        //ctor dtor
        Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed);
        virtual ~Enemy();

        //Atualizacao e grafico personagem
        void Update_Enemy(float deltaTime, Player &player);

    public:
        float damage;

    private:
        //CD == cooldown
        float AICD;

        //DEFINE SE INIMIGO DEVE ATIRAR:
        bool shooting;
};
