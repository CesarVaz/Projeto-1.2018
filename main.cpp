#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Enemy.h"

using namespace std;

static const float VIEW_WIDTH = 1024.0f;    /*largura da tela*/
static const float VIEW_HEIGHT = 600.0f;    /*altura da tela*/
static const float def_Speed = 500.0f;      /*velocidade do personagem*/
static const unsigned int nPlatforms = 6;   /*numero de plataformas*/
static const unsigned int nEnemies = 4;     /*numero de inimigos*/

void ResizeView(const sf::RenderWindow &window, sf::View &view)
{
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT * aspectRatio);
}

int main()
{
    unsigned int i, j;
    int randPlatformPos;
    int randEnemyPos;
    srand (time(NULL));

    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Jogo de Tiro em 2D", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/Player_tex.png");
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("textures/Inimigo.png");
    sf::Texture groundTexture;
    groundTexture.loadFromFile("textures/ground.png");
    sf::Texture bushTexture;
    bushTexture.loadFromFile("textures/bush.png");
    sf::Texture floorTexture;
    floorTexture.loadFromFile("textures/floor.png");
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("textures/Bullet.png");

    Player player(&playerTexture, sf::Vector2u(3, 4), 0.1f, &bulletTexture, def_Speed);
    Enemy enemy(&enemyTexture, sf::Vector2u(3, 4), 0.1f, &bulletTexture, def_Speed);
    vector<Enemy> vEnemy;

    //PRIMEIRA PLATAFORMA (USADA COMO REFERENCIA)
    Platform platform(&groundTexture, sf::Vector2f(576.0f, 192.0f), sf::Vector2f(0.0f, 0.0f));
    vector<Platform> vPlatform;
    vPlatform.push_back(platform);
    Platform floor(&floorTexture, sf::Vector2f(576.0f, 48.0f), sf::Vector2f(platform.getBody().getPosition().x, platform.getBody().getPosition().y - platform.getBody().getSize().y / 2));
    vector<Platform> vFloor;
    vFloor.push_back(floor);

    for(i = vPlatform.size(); i < nPlatforms; i++)
    {
        vPlatform.push_back(platform);

        randPlatformPos = rand() % 3;
        randPlatformPos --;

        //COLOCANDO PLATAFORMA[i] A FRENTE DA ANTERIOR E EM ALTURA ALEATORIA
        vPlatform[i].setBodyPosition(vPlatform[i-1].getBody().getPosition().x + vPlatform[i-1].getBody().getSize().x
        , vPlatform[i-1].getBody().getPosition().y + randPlatformPos * (vPlatform[i-1].getBody().getSize().y));

        //O MESMO COM FLOOR
        vFloor.push_back(floor);
        vFloor[i].setBodyPosition(vFloor[i-1].getBody().getPosition().x + vPlatform[i-1].getBody().getSize().x
        , vFloor[i-1].getBody().getPosition().y + randPlatformPos * (vPlatform[i-1].getBody().getSize().y));
    }

    //CRIAR INIMIGOS
    while(vEnemy.size() < nEnemies)
    {
        randEnemyPos = rand() % vPlatform.size();
        vEnemy.push_back(enemy);
        //DISTRIBUI INIMIGOS PELAS PLATAFORMAS DE FORMA ALEATÓRIA
        vEnemy[vEnemy.size() - 1].setBodyPosition(vPlatform[randEnemyPos].getBody().getPosition().x
        , vPlatform[randEnemyPos].getBody().getPosition().y - vPlatform[randEnemyPos].getBody().getSize().y);
    }

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            deltaTime = clock.restart().asSeconds();
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                deltaTime = clock.restart().asSeconds();
                ResizeView(window, view);
                break;
            }
        }
        //INPUT
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move("right");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move("left");
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.jump();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player.shoot();

        player.Update_Player(deltaTime);

        view.setCenter(player.GetPosition());
        window.clear(sf::Color(150, 150, 150));
        window.setView(view);

        //COLISAO DO JOGADOR E DOS TIROS DO JOGADOR COM AS PLATAFORMAS + DESENHO DAS PLATAFORMAS E FLOORS
        for(i = 0; i < vPlatform.size(); i++)
        {
            player.CheckCollision_Player(vPlatform[i]);
            player.CheckCollision_ProjectileVector(vPlatform[i].getBody());

            vFloor[i].Draw(window);
            vPlatform[i].Draw(window);
        }

        //COLISAO DOS INIMIGOS COM PLATAFORMA - INTERAÇAO DOS PROJÉTEIS - UPDATE E DRAW DOS INIMIGOS
        for(i = 0; i < vEnemy.size(); i++)
        {
            for(j = 0; j< vPlatform.size(); j++)
            {
                vEnemy[i].CheckCollision_Player(vPlatform[j]);
                vEnemy[i].CheckCollision_ProjectileVector(vPlatform[j].getBody());
            }
            if(vEnemy[i].getDead() == false)
                player.CheckCollision_ProjectileVector_Damage(vEnemy[i].getBody(), vEnemy[i].damage);

            vEnemy[i].CheckCollision_ProjectileVector_Damage(player.getBody(), player.damage);

            vEnemy[i].Update_Player(deltaTime, player);
            vEnemy[i].Draw_Player(window);

            vEnemy[i].Update_Projectile(deltaTime);
            vEnemy[i].Draw_Projectile(window);
        }

        player.Update_Projectile(deltaTime);
        player.Draw_Projectile(window);
        player.Draw_Player(window);

        window.display();
    }

    return 0;
}
