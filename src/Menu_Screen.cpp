#include "Menu_Screen.h"


Menu_Screen::Menu_Screen(float width, float height, int& stateValue)
{
	if (!font.loadFromFile("textures/arial.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	instructions.setFont(font);
	instructions.setCharacterSize(18);
	instructions.setFillColor(sf::Color::Green);
	instructions.setString("Instrucoes:\nSetas (Cima/Baixo): Escolher\nEnter: Selecionar\nEm jogo:\nSetas: Controlar\nEspa�o: Atirar");
	instructions.setPosition(sf::Vector2f(width / 12, height / 12));

	selectedItemIndex = 0;
	stateValue = 3;
}

Menu_Screen::~Menu_Screen()
{

}

void Menu_Screen::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}

	window.draw(instructions);
}

void Menu_Screen::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu_Screen::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
