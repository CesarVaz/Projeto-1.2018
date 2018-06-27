#pragma once

#include "Player.h"

class UI :	public Platform, public Animation
{
public:
	UI(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f size, sf::Vector2f position);
	~UI();
	void Update_HealthBar(int playerDamage);

private:
	int NextDamage;
};

