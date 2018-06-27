#include "UI.h"



UI::UI(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f size, sf::Vector2f position):
	Animation(texture, imageCount), Platform(texture, size, position)
{
	NextDamage = 40;
}


UI::~UI()
{
}


void UI::Update_HealthBar(int playerDamage)
{
	if (playerDamage == NextDamage)
	{
		Update(0);
		NextDamage += 80;
	}
	body.setTextureRect(uvRect);
}