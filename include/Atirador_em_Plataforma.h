#pragma once

#include "Game_Screen.h"
#include "Menu_Screen.h"

#include <stack>

class Atirador_em_Plataforma
{
public:
	Atirador_em_Plataforma();
	~Atirador_em_Plataforma();

	void ResizeView(const sf::RenderWindow &window, sf::View &view);
	void Loop_Janela();

private:
	int stateValue;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture groundTexture;
	sf::Texture floorTexture;
	sf::Texture bulletTexture;
	sf::Texture healthTexture;

	//Menu_Screen menu(VIEW_WIDTH, VIEW_HEIGHT);
	std::stack<Game_Screen> GameStack;
	std::stack<Menu_Screen> MenuStack;

	//INSTANCIANDO JANELA E VISAO DO JOGADOR
	sf::RenderWindow window; // (sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Jogo de Tiro em 2D", sf::Style::Close | sf::Style::Resize);
	sf::View view; // (sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	float deltaTime = 0.0f;     //DELTA TEMPO: UTILIZADO NA ATUALIZACAO DOS QUADROS
	sf::Clock clock;            //RELOGIO: UTILIZADO PARA INCREMENTAR DELTA TEMPO
};

