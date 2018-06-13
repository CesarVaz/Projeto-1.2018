#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
		Animation(sf::Texture* texture, sf::Vector2u imageCount);
        Animation(sf::Texture* texture);

        void Update(int row, float deltaTime, bool faceRight);
		void Update(int row);

    protected:
        sf::IntRect uvRect;
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float totalTime;
        float switchTime;

};
