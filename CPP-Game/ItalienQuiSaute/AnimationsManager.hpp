#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TexturesManager.hpp"

class AnimationManager
{
public:
	std::vector<sf::Texture> GetAnimationArray(const int& index)
	{
		if (runSprites.empty())
		{
			runSprites.push_back(TexturesManager::getTexture(4));
			runSprites.push_back(TexturesManager::getTexture(5));
			runSprites.push_back(TexturesManager::getTexture(6));
		}
		else if (jumpSprites.empty())
		{
			jumpSprites.push_back(TexturesManager::getTexture(7));
		}

		switch (index)
		{
		case 0:
			return runSprites;
			break;
		case 1:
			return jumpSprites;
			break;
		}
	}

private:
	std::vector<sf::Texture> runSprites;
	std::vector<sf::Texture> jumpSprites;
};