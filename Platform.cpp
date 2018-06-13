#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

void Platform::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::RectangleShape Platform::getBody()
{
    return body;
}

void Platform::bodyMove(float moveX, float moveY)
{
    body.move(moveX, moveY);
}

void Platform::setBodyPosition(float x, float y)
{
    body.setPosition(x, y);
}
