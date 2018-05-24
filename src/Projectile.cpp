#include "Projectile.h"

Projectile::Projectile(Player player)
{
    this->faceRight = player.getFaceRight();
    body.setSize(sf::Vector2f(20,10));
    body.setOrigin(body.getSize()/2.0f);
    iniPosition = player.GetPosition();

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
    isAvailable = true;
}

Projectile::~Projectile()
{
    //dtor
}

void Projectile::Update(float deltaTime)
{
    if(isAvailable == false)
    {
        if(faceRight == true)
        {
            velocity.x = 8000.0f;
        }

        else
        {
            velocity.x = -8000.0f;
        }
        velocity.y += 981.0f * deltaTime;
        body.move(velocity * deltaTime);
    }


}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}


void Projectile::StaticCheckCollision(Platform &platform, Player &player)
{
    if(body.getGlobalBounds().intersects(platform.getBody().getGlobalBounds()))
    {
        setIsAvailable(true);
        velocity.y = 0.0f;
        velocity.x = 0.0f;
    }

    /* RETIRAR DO COMENTARIO QUANTO TIVER OUTROS "PLAYERS"
    if(body.getGlobalBounds().intersects(player.getBody().getGlobalBounds()))
    {
        setIsAvailable(true);
        velocity.y = 0.0f;
        velocity.x = 0.0f;
    }
    */
}

void Projectile::setBodyPosition(sf::Vector2f playerPos, bool faceRight)
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

sf::RectangleShape Projectile::getBody()
{
    return body;
}

void Projectile::setIsAvailable(bool available)
{
    isAvailable = available;
}

bool Projectile::getIsAvailable()
{
    return isAvailable;
}

bool Projectile::setFaceRight(bool faceRight)
{
    this->faceRight = faceRight;
}

            sf::Vector2f Projectile::setVelocityY(float y)
            {
                velocity.y = y;
            }
