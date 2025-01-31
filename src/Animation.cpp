#include "Animation.h"

//Para imagens variaveis:
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

//IMAGENS QUE NAO VARIAM COM O TEMPO
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount)
{
	this->imageCount = imageCount;
	switchTime = 0.0f;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

//Para imagens unicas:
Animation::Animation(sf::Texture* texture)
{
    imageCount.x = 1;
    imageCount.y = 1;
    switchTime = 0.0;
    totalTime = 0.0f;
    currentImage.x = 0;

    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

}

//Atualiza quando requisitado
void Animation::Update(int row)
{
	currentImage.x++;
	currentImage.y = row;

	currentImage.x++;

	if (currentImage.x >= imageCount.x)
	{
		currentImage.x = 0;
	}

	uvRect.top = currentImage.y * uvRect.height;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width);
}