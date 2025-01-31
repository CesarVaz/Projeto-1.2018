#include "Player.h"

static const float sCD = 0.25f;
static const float jCD = 1.0f;

//ctor dtor
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed):
        Animation(texture, imageCount, switchTime), projectile(projTexture)
{
    this->speed = speed;
    row = 0;
    faceRight = true;
    setBodyPosition(0.0f, -192.0f);
    hitTheFloor = false;
    jumpHeight = 180.0f;

    shootCD = sCD;
    jumpCD = jCD;

    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setTexture(texture);

    damage = 0;
    dead = false;
}

//sets
void Player::setSpeed(float _speed)
{
    speed = _speed;
}

void Player::setBodyPosition(float x, float y)
{
    body.setPosition(x, y);
}

//gets
sf::RectangleShape Player::getBody()
{
    return body;
}

sf::Vector2f Player::GetPosition()
{
    return body.getPosition();
}

bool Player::getFaceRight()
{
    return faceRight;
}

bool Player::getDead()
{
    return dead;
}

//interacoes com o ambiente
//do personagem
void Player::CheckCollision_Player(sf::RectangleShape platformBody)
{
    if((body.getGlobalBounds().left + body.getGlobalBounds().width) < platformBounds.left || body.getGlobalBounds().left > (platformBounds.left + platformBounds.width))
        hitTheFloor = false;

    if(body.getGlobalBounds().intersects(platformBody.getGlobalBounds()))
    {
        platformBounds = platformBody.getGlobalBounds();

        if(body.getPosition().y > platformBody.getPosition().y + platformBody.getSize().y / 2)
        {
            body.move(0.0, 1.0);
        }

        else
        if(body.getPosition().y < platformBody.getPosition().y - platformBody.getSize().y / 2)
        {
            body.move(0.0, - 1.0);
            hitTheFloor = true;
        }

        else
        if(body.getPosition().x < platformBody.getPosition().x - platformBody.getSize().x / 2)
        {
            body.move(- 1.0, 0.0);
        }

        else
        if(body.getPosition().x > platformBody.getPosition().x + platformBody.getSize().x / 2)
        {
            body.move(1.0, 0.0);
        }

    }
}

//do tiro
void Player::CheckCollision_ProjectileVector(sf::RectangleShape target)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].CheckCollision(target);

        if(vectProj[i].collision == true)
        {
            vectProj.erase (vectProj.begin()+i);
            vectProj.shrink_to_fit();
        }
    }
}

void Player::CheckCollision_ProjectileVector_Damage(sf::RectangleShape target, int &damage)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].CheckCollision_Damage(target, damage);

        if(vectProj[i].collision == true)
        {
            vectProj.erase (vectProj.begin()+i);
            vectProj.shrink_to_fit();
        }
    }
}

//INPUTS
void Player::move(string direction)
{
    if(dead == false)
    {
        if(direction == "left")
        {
            velocity.x -= speed;
        }

        if(direction == "right")
        {
            velocity.x += speed;
        }
    }
}

void Player::jump()
{
    if(dead == false)
    {
        if (jumpCD >= jCD && hitTheFloor == true)
        {
            velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
            jumpCD = 0.0f;
            hitTheFloor = false;
        }
    }
}

void Player::shoot()
{
    if(dead == false)
    {
        if (shootCD >= sCD)
        {
            shootCD = 0.0f;
            vectProj.push_back(projectile);
            vectProj[vectProj.size() - 1].addVelocity(velocity);
            vectProj[vectProj.size() - 1].setFaceRight(getFaceRight());
            vectProj[vectProj.size() - 1].setBodyPosition(body.getPosition(), getFaceRight());
        }
    }
}

//Atualizacao e grafico personagem
void Player::Update_Player(float deltaTime)
{
    shootCD += deltaTime;
    jumpCD += deltaTime;

    //gravidade
    velocity.y += 981.0f * deltaTime;
    if (hitTheFloor == true)
        velocity.y = 0.0f;

	if (velocity.y > 3000.0f)
		dead = true;

    if(damage >= 200 && dead == false)
    {
        if(faceRight == true)
            body.rotate(270);
        else
            body.rotate(90);

        hitTheFloor = false;

        row = 3;

        dead = true;
    }

    if(dead == false)
    {
        if(velocity.x == 0.0f)
            row = 1;
        else
            row = 2;
    }

    if(velocity.x > 0.0f)
        faceRight = true;
    if(velocity.x < 0.0f)
        faceRight = false;

    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].totalTime += deltaTime;
        if(vectProj[i].totalTime >= vectProj[i].duration)
        {
            vectProj.erase (vectProj.begin()+i);
            vectProj.shrink_to_fit();
        }
    }

    Update(row, deltaTime, faceRight);
    body.setTextureRect(uvRect);
    body.move(velocity * deltaTime);
    velocity.x = 0.0f;
}


void Player::Draw_Player(sf::RenderWindow& window)
{
    window.draw(body);
}

//Atualizacao e grafico tiro
void Player::Update_Projectile(float deltaTime)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].Update_Projectile(deltaTime);
    }
}

void Player::Draw_Projectile(sf::RenderWindow& window)
{
    for(i = 0; i < vectProj.size(); i++)
    {
        vectProj[i].Draw(window);
    }
}
