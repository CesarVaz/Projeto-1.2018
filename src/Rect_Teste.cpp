#include "Rect_Teste.h"

Rect_Teste::Rect_Teste()
{
    body.setSize(sf::Vector2f(10,5));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(200.0f, -400.0f);
    duration = 2.0f;
    totalTime = 0.0f;
}

Rect_Teste::~Rect_Teste()
{
    //dtor
}

void Rect_Teste::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Rect_Teste::setBodyPosition(sf::Vector2f playerPos, bool faceRight)
{
    iniPosition = playerPos;
    if(faceRight == true)
    {
        iniPosition.x += 65.0f;
        iniPosition.y += 7.5f;
    }
    else
    {
        iniPosition.x -= 65.0f;
        iniPosition.y += 7.5f;
    }
    body.setPosition(iniPosition);
}

void Rect_Teste::setToDelete(bool toDelete)
{
    this->toDelete = toDelete;
}

void Rect_Teste::StaticCheckCollision(sf::RectangleShape target)
{
    if(body.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        setToDelete(true);
        //cont--;
    }

}

sf::Vector2f Rect_Teste::getBodyPos()
{
    return body.getPosition();
}
