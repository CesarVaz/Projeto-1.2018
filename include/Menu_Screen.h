#pragma once
#include "SFML/Graphics.hpp"

static const int MAX_NUMBER_OF_ITEMS = 3;

class Menu_Screen
{
public:
	Menu_Screen(float width, float height, int& stateValue);
	~Menu_Screen();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Text instructions;

};
