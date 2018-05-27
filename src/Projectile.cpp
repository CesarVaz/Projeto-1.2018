#include "Projectile.h"

Projectile::Projectile(sf::Texture* projTexture):
    animation(projTexture)
{
    body.setSize(sf::Vector2f(10,5));
    body.setOrigin(body.getSize()/2.0f);
    body.setTexture(projTexture);
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
            velocity.x = 2000.0f;
        }

        else
        {
            velocity.x = -2000.0f;
        }
        velocity.y += 981.0f * deltaTime;
        body.move(velocity * deltaTime);
        animation.Update(0, 0.0f, faceRight);
        body.setTextureRect(animation.uvRect);
    }

}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}


void Projectile::StaticCheckCollision(sf::RectangleShape target)
{
    if(body.getGlobalBounds().intersects(target.getGlobalBounds()))
    {
        setIsAvailable(true);
        velocity.y = 0.0f;
        velocity.x = 0.0f;
    }

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

void Projectile::setFaceRight(bool faceRight)
{
    this->faceRight = faceRight;
}

void Projectile::setVelocityY(float y)
{
    velocity.y = y;
}

void Projectile::addVelocity(sf::Vector2f velocity)
{
    this->velocity += velocity;
}
