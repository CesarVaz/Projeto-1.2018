#include "Enemy.h"

static const float sCD = 0.25f;
static const float jCD = 0.5f;

//ctor dtor
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Texture* projTexture, float speed):
        Player(texture, imageCount, switchTime, projTexture, speed)
{
    shooting = false;
    setBodyPosition(900.0f, -400.0f);
    damage = 0.0f;
}

//Atualizacao e grafico personagem
void Enemy::Update_Player(float deltaTime, Player &player)
{
    velocity.x = 0.0f;
    jumpHeight = 180.0f;
    shootCD += deltaTime;
    jumpCD += deltaTime;

    //gravidade
    velocity.y += 981.0f * deltaTime;
    if (hitTheFloor == true)
        velocity.y = 0.0f;

    if(damage >= 40 && dead == false)
    {
        hitTheFloor = false;
        row = 3;

        if(faceRight == true)
            body.rotate(270);
        else
            body.rotate(90);

        dead = true;
    }

    if(dead == false)
    {
        //tiro
        if (shootCD >= sCD)
        {
            //Checa se o jogador está na linha de tiro & VIVO
            if((player.GetPosition().y + player.getBody().getSize().y / 2) >= (body.getPosition().y) &&
            (player.GetPosition().y - player.getBody().getSize().y / 2) <= (body.getPosition().y) &&
            ((player.GetPosition().x > body.getPosition().x && faceRight == true) ||
            (player.GetPosition().x < body.getPosition().x && faceRight == false)) &&
            (abs(player.GetPosition().x - body.getPosition().x) <= 1000.0f) && player.getDead() == false)
            {
                shooting = true;
                vectProj.push_back(projectile);
                vectProj[vectProj.size() - 1].addVelocity(velocity);
                shootCD = 0.0f;
                vectProj[vectProj.size() - 1].setFaceRight(getFaceRight());
                vectProj[vectProj.size() - 1].setBodyPosition(body.getPosition(), getFaceRight());
            }

            else
                shooting = false;
        }

        for(i = 0; i < vectProj.size(); i++)
        {
            vectProj[i].totalTime += deltaTime;

            if(vectProj[i].totalTime >= vectProj[i].duration)
            {
                vectProj.erase (vectProj.begin()+i);
            }
        }

        //movimento
        if(shooting == false)
        {
            if(faceRight == true)
            {
                velocity.x += speed / 2.0f;
            }
            else
            {
                velocity.x -= speed / 2.0f;
            }

            if(body.getPosition().x < (globalBounds.left + 100.0f) || body.getPosition().x > (globalBounds.left + globalBounds.width - 100.0f) )
            {
                velocity.x *= -1.0f;
            }
        }

        if(velocity.x == 0.0f)
            row = 1;
        else
            row = 2;
    }

    if(velocity.x > 0.0f)
        faceRight = true;
    if(velocity.x < 0.0f)
        faceRight = false;


    Update(row, deltaTime, faceRight);
    body.setTextureRect(uvRect);
    body.move(velocity * deltaTime);
}
