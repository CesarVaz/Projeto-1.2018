#pragma once

#include "Player.h"


class Enemy: public Player
{
    public:
        //ctor dtor
        Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed);

        //Atualizacao e grafico personagem
        void Update_Player(float deltaTime, Player &player);

    public:
        //float damage;

    private:
        //DEFINE SE INIMIGO DEVE ATIRAR:
        bool shooting;

};
