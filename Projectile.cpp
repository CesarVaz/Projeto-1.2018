#include "Projectile.h"

static const float bul_Speed = 2000.0f;
static const int dmg = 20;

//ctor dtor
Projectile::Projectile(sf::Texture* projTexture):
    Animation(projTexture)
{
    body.setSize(sf::Vector2f(10,5));
    body.setOrigin(body.getSize()/2.0f);
    body.setTexture(projTexture);
    velocity.x = 0.0f;
    velocity.y = 0.0f;
    collision = false;
    duration = 2.0f;
    totalTime = 0.0f;
}

//sets
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

void Projectile::setFaceRight(bool faceRight)
{
    this->faceRight = faceRight;
}

void Projectile::addVelocity(sf::Vector2f velocity)
{
    this->velocity += velocity;
}

//gets
sf::RectangleShape Projectile::getBody()
{
    return body;
}

//interacoes com o ambiente
void Projectile::CheckCollision(sf::RectangleShape target)
{
    if(collision == false)
    {
        if(body.getGlobalBounds().intersects(target.getGlobalBounds()))
        {
            velocity.y = 0.0f;
            velocity.x = 0.0f;
            collision = true;
        }
    }
}

void Projectile::CheckCollision_Damage(sf::RectangleShape target, int &damage)
{
    if(collision == false)
    {
        if(body.getGlobalBounds().intersects(target.getGlobalBounds()))
        {
            velocity.y = 0.0f;
            velocity.x = 0.0f;
            collision = true;
            damage += dmg;
        }
    }
}

//Atualizacao e grafico tiro
void Projectile::Update_Projectile(float deltaTime)
{
        if(faceRight == true)
        {
            velocity.x = bul_Speed;
        }

        else
        {
            velocity.x = -bul_Speed;
        }
        velocity.y += 981.0f * deltaTime;
        body.move(velocity * deltaTime);
        Update(0, 0.0f, faceRight);
        body.setTextureRect(uvRect);
}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
