#pragma once

#include "Enemy.h"
#include "UI.h"

class Game_Screen
{
    public:
        Game_Screen(sf::Texture* playerTexture, sf::Texture* enemyTexture, sf::Texture* groundTexture, sf::Texture* floorTexture, sf::Texture* bulletTexture, sf::Texture* healthTexture, int& stateValue);
        ~Game_Screen();

        void Loop(sf::RenderWindow& window, sf::View &view, float deltaTime, int& stateValue);
        void input(int &stateValue);

    protected:

    private:
        Player player;
        Enemy enemy;
        Platform platform;
        Platform floor;
		UI healthBar;

        vector<Enemy> vEnemy;
        vector<Platform> vPlatform;
        vector<Platform> vFloor;

        unsigned int i, j;      //INDICES
        int randPlatformPos;    //RECEBE N ALEATORIO PARA ALTURA DA PROXIMA PLATAFORMA
        int randEnemyPos;       //RECEBE N ALEATORIO PARA DEFINIR POSICAO INICIAL DO INIMIGO
};
