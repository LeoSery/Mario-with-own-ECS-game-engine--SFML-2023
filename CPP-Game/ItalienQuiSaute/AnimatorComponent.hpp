#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TexturesManager.hpp"

class AnimatorComponent : public Component
{
public:
	AnimatorComponent()
	{
		Tag = "ANIMATOR";
		if (runTextures.empty())
		{
			runTextures.push_back(TexturesManager::getTexture(101));
			runTextures.push_back(TexturesManager::getTexture(102));
			runTextures.push_back(TexturesManager::getTexture(103));
		}

		winTexture = TexturesManager::getTexture(104);
		idleTexture = TexturesManager::getTexture(105);
		jumpTexture = TexturesManager::getTexture(106);
	}

	sf::Texture PlayAnimation(movementState currentMovementState, sf::Time deltaTime)
	{
		std::vector<sf::Texture> currentTextureArray;
		int currentTexureIndex = 0;
		time += deltaTime;

		if (currentMovementState == movementState::WALK)
		{
			currentTextureArray = runTextures;

			if (index >= currentTextureArray.size())
			{
				index = 0;
			}

			if (time.asMilliseconds() > 200)
			{
				time = sf::Time(sf::seconds(0));

				sf::Texture texture = currentTextureArray.at(index);
				index++;
				return texture;
			}
		}
		else if (currentMovementState == movementState::JUMP)
			return jumpTexture;
		else if (currentMovementState == movementState::IDLE)
			return idleTexture;
		else if (currentMovementState == movementState::VICTORY)
			return winTexture;
	}

private:
	sf::Time time;
	int index;
	std::vector<sf::Texture> runTextures;
	sf::Texture jumpTexture;
	sf::Texture idleTexture;
	sf::Texture winTexture;
};