#include "Game_Screen.h"

static const float VIEW_WIDTH = 1024.0f;    /*largura da tela*/
static const float VIEW_HEIGHT = 600.0f;    /*altura da tela*/
static const float def_Speed = 500.0f;      /*velocidade do personagem*/
static const unsigned int nPlatforms = 6;   /*numero de plataformas*/
static const unsigned int nEnemies = 4;     /*numero de inimigos*/

Game_Screen::Game_Screen(sf::Texture* playerTexture, sf::Texture* enemyTexture, sf::Texture* groundTexture, sf::Texture* floorTexture, sf::Texture* bulletTexture, sf::Texture* healthTexture, int& stateValue):
    player(playerTexture, sf::Vector2u(3, 4), 0.1f, bulletTexture, def_Speed),
    enemy(enemyTexture, sf::Vector2u(3, 4), 0.1f, bulletTexture, def_Speed),
    platform(groundTexture, sf::Vector2f(576.0f, 192.0f), sf::Vector2f(0.0f, 0.0f)),
    floor(floorTexture, sf::Vector2f(576.0f, 48.0f), sf::Vector2f(platform.getBody().getPosition().x, platform.getBody().getPosition().y - platform.getBody().getSize().y / 2)),
	healthBar(healthTexture, sf::Vector2u(6, 1), sf::Vector2f(200.0f, 30.0f), sf::Vector2f(0.0f, 0.0f))
{
    vPlatform.push_back(platform);
    vFloor.push_back(floor);

    //CRIANDO VETOR DE PLATAFORMAS A PARTIR DA PRIMEIRA PLATAFORMA (REFERENCIA)
    srand (time(NULL));     //SEMENTE PARA O RANDOM (BASEADO NO RELOGIO)
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

    stateValue = 0;
}

Game_Screen::~Game_Screen()
{

}

void Game_Screen::Loop(sf::RenderWindow& window, sf::View &view, float deltaTime, int &stateValue)
{
    input(stateValue);

    player.Update_Player(deltaTime);            //ATUALIZA POSICAO E ANIMACAO DO PERSONAGEM

    view.setCenter(player.GetPosition());       //ATRIBUI A POSICAO DO JOGADOR AO CENTRO DE VIEW
    window.clear(sf::Color(150, 150, 150));

    window.setView(view);       //ATRIBUI VIEW A A VISAO DA JANELA

    //COLISAO DO JOGADOR E DOS TIROS DO JOGADOR COM AS PLATAFORMAS + DESENHO DAS PLATAFORMAS E FLOORS
    for(i = 0; i < vPlatform.size(); i++)
    {
        player.CheckCollision_Player(vPlatform[i].getBody());
        player.CheckCollision_ProjectileVector(vPlatform[i].getBody());

        vFloor[i].Draw(window);
        vPlatform[i].Draw(window);
    }

    //COLISAO DOS INIMIGOS COM PLATAFORMA - INTERAÇAO DOS PROJÉTEIS - UPDATE E DRAW DOS INIMIGOS
    for(i = 0; i < vEnemy.size(); i++)
    {
        for(j = 0; j< vPlatform.size(); j++)
        {
            vEnemy[i].CheckCollision_Player(vPlatform[j].getBody());
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
	
	healthBar.setBodyPosition(view.getCenter().x - view.getSize().x / 3, view.getCenter().y - view.getSize().y / 3);
	healthBar.Update_HealthBar(player.damage);
	healthBar.Draw(window);

    if(player.getDead() == true)
        stateValue = 4;
}

void Game_Screen::input(int &stateValue)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.move("right");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player.move("left");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player.jump();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        player.shoot();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        stateValue = 4;
}
