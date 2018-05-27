#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"
#include <stdlib.h>

using namespace std;

static const float VIEW_HEIGHT = 1024.0f;
static const float VIEW_WIDTH = 600.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x / float(window.getSize().y));
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDTH * aspectRatio);
}

int main()
{
                            int i = 0;

    float def_Speed = 500.0f;

    sf::RenderWindow window(sf::VideoMode(VIEW_HEIGHT, VIEW_WIDTH), "Jogo de Tiro em 2D", sf::Style::Close | sf::Style::Resize);

    sf::View view(sf::Vector2f(0.0f, 0.0f),sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/Player_tex.png");

    sf::Texture groundTexture;
    groundTexture.loadFromFile("textures/ground.png");

    sf::Texture bushTexture;
    bushTexture.loadFromFile("textures/bush.png");

    sf::Texture floorTexture;
    floorTexture.loadFromFile("textures/floor.png");

    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("textures/Bullet.png");

    Player player(&playerTexture, sf::Vector2u(3, 4), 0.1f, def_Speed, &bulletTexture);

    Platform ground(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(1020.0f, 0.0f));
    Platform ground2(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(1596.0f, 156.0f));
    Platform ground3(&groundTexture, sf::Vector2f(576.0f, 156.0f), sf::Vector2f(444.0f, -156.0f));
    Platform bush(&bushTexture, sf::Vector2f(468.0f, 140.0f), sf::Vector2f(500.0f, 10.0f));
    Platform floor(&floorTexture, sf::Vector2f(576.0f, 36.0f), sf::Vector2f(1020.0f, -95.0f));


    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            deltaTime = clock.restart().asSeconds();
            switch (evnt.type)
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

        player.Update(deltaTime);

        view.setCenter(player.GetPosition());

        player.CheckActivePlatform(ground);
        player.CheckActivePlatform(ground2);
        player.CheckActivePlatform(ground3);

        player.StaticCheckCollision(ground);
        player.StaticCheckCollision(ground2);
        player.StaticCheckCollision(ground3);

        player.projectile.StaticCheckCollision(ground.getBody());
        player.projectile.StaticCheckCollision(ground2.getBody());
        player.projectile.StaticCheckCollision(ground3.getBody());
        player.projectile.StaticCheckCollision(player.getBody());

        player.projectile.Update(deltaTime);

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);

        floor.Draw(window);
        player.Draw(window);
        ground.Draw(window);
        ground2.Draw(window);
        ground3.Draw(window);
        bush.Draw(window);

            //DESENHA O TIRO
            if(player.projectile.getIsAvailable() == false)
            {
                player.projectile.Draw(window);
            }

        window.display();
    }

    return 0;
}
