#include "Player.h"

static const float sCD = 0.25f;
static const float jCD = 0.5f;

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Texture* projTexture):
        animation(texture, imageCount, switchTime), projectile(projTexture)
    {
        this->speed = speed;
        row = 0;
        faceRight = true;
        setBodyPosition(400.0f, -400.0f);

        shootCD = sCD;
        jumpCD = jCD;

        projectile.setFaceRight(this->faceRight);
        projectile.setBodyPosition(body.getPosition(), faceRight);

        texture->setSmooth(true);
        body.setSize(sf::Vector2f(100.0f, 150.0f));
        body.setOrigin(body.getSize()/2.0f);
        body.setTexture(texture);

    }

Player::~Player()
{
    //dtor
}

void Player::Update(float deltaTime)
{
    velocity.x = 0.0f;
    jumpHeight = 180.0f;
    shootCD += deltaTime;
    jumpCD += deltaTime;

    //GRAVIDADE
    velocity.y += 981.0f * deltaTime;

    //MOVIMENTO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += speed;
    }

    //PULO
    if (jumpCD >= jCD)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hitTheFloor == true)
        {
            velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
            hitTheFloor = false;
            jumpCD = 0.0f;
        }
    }

    //TIRO
    if (shootCD >= sCD)
    {
        projectile.setVelocityY(0.0f);
        projectile.setIsAvailable(true);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //if(projectile.getIsAvailable() == true)
            //{
                projectile.addVelocity(velocity);
                shootCD = 0.0f;
                projectile.setIsAvailable(false);
                projectile.setFaceRight(getFaceRight());
                projectile.setBodyPosition(getBody().getPosition(), getFaceRight());
            //}
        }
    }

    if(hitTheFloor == true)
    {
        velocity.y = 0.0;
    }

    if(velocity.x == 0.0f)
    {
        row = 1;
    }

    else
    {
        row = 2;

        if(velocity.x > 0.0f)
        {
            faceRight = true;
        }
        else
        {
            faceRight = false;
        }
    }

    animation.Update(row, deltaTime, faceRight);
    body.setTextureRect(animation.uvRect);
    body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

sf::Vector2f Player::GetPosition()
{
    return body.getPosition();
}

void Player::setSpeed(float _speed)
{
    speed = _speed;
}

void Player::setBodyPosition(float x, float y)
{
    body.setPosition(x, y);
}

sf::RectangleShape Player::getBody()
{
    return body;
}

void Player::CheckActivePlatform(Platform &platform)
{
    if(body.getPosition().x > platform.getBody().getPosition().x + (platform.getBody().getSize().x / 2)  ||  body.getPosition().x < platform.getBody().getPosition().x - (platform.getBody().getSize().x / 2))
        platform.set_isActivePlatform(false);

    else
        platform.set_isActivePlatform(true);

    if(platform.get_isActivePlatform() == true)
    {
        if((body.getPosition().y - (platform.getBody().getPosition().y + platform.getBody().getSize().y / 2) < -250.0f))
        hitTheFloor = false;
    }
}

void Player::StaticCheckCollision(Platform &platform)
{
    if(body.getGlobalBounds().intersects(platform.getBody().getGlobalBounds()))
    {
        if(body.getPosition().y > platform.getBody().getPosition().y + platform.getBody().getSize().y / 2)
        {
            body.move(0.0, 1.0);
            velocity.y = 0.0f;
        }

        else
        if(body.getPosition().y < platform.getBody().getPosition().y - platform.getBody().getSize().y / 2)
        {
            body.move(0.0, - 1.0);
            //velocity.y = 0.0f;
            hitTheFloor = true;
        }

        else
        if(body.getPosition().x < platform.getBody().getPosition().x - platform.getBody().getSize().x / 2)
        {
            body.move(- 1.0, 0.0);
            velocity.x = 0.0f;
        }

        else
        if(body.getPosition().x > platform.getBody().getPosition().x + platform.getBody().getSize().x / 2)
        {
            body.move(1.0, 0.0);
            velocity.x = 0.0f;
        }
    }
}

void Player::MovableCheckCollision(Platform &platform, float mass)
{
    if(abs(mass) > 10.0)
        mass = 10.0f;

    if(body.getGlobalBounds().intersects(platform.getBody().getGlobalBounds()))
    {

        if(body.getPosition().y > platform.getBody().getPosition().y + platform.getBody().getSize().y / 2)
        {
            body.move(0.0, 1.0);
            velocity.y = 0.0f;
        }

        else
        if(body.getPosition().y < platform.getBody().getPosition().y - platform.getBody().getSize().y / 2)
        {
            body.move(0.0, - 1.0);
            velocity.y = 0.0f;
            hitTheFloor = true;
        }

        else
        if(body.getPosition().x < platform.getBody().getPosition().x - platform.getBody().getSize().x / 2)
        {
            body.move(- 1.0, 0.0);
            platform.bodyMove(10.0 - abs(mass) , 0.0f);
            velocity.x = 0.0f;
        }

        else
        if(body.getPosition().x > platform.getBody().getPosition().x + platform.getBody().getSize().x / 2)
        {
            body.move(1.0, 0.0);
            platform.bodyMove(-(10.0 - abs(mass)) , 0.0f);
            velocity.x = 0.0f;
        }
    }
}

bool Player::getFaceRight()
{
    return faceRight;
}
