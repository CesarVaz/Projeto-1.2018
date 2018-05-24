#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
    animation(texture, imageCount, switchTime)
{

    this->speed = speed;
    def_Speed = speed;
    row = 0;
    faceRight = true;
    hitTheFloor = false;
    texture->setSmooth(true);
    body.setSize(sf::Vector2f(108.0f, 156.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(1020.0f, -150.0f);
    body.setTexture(texture);
}

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f Position):
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceRight = true;

    texture->setSmooth(true);
    body.setSize(sf::Vector2f(100.0f, 150.0f));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(Position);
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

    //gravidade:
    velocity.y += 981.0f * deltaTime;
//if(hitTheFloor == true)
//{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x += speed;
    }
//}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && hitTheFloor == true)
    {
        velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
        hitTheFloor = false;
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

    /*
    if(platform.get_isActivePlatform() == true)
    {
        cout << (body.getPosition().y - (platform.getBody().getPosition().y + platform.getBody().getSize().y / 2));
    }
    */

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
