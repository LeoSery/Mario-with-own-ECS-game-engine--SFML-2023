#pragma once

#include "TexturesManager.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

class AnimationManager
{
public:
	std::vector<sf::Texture> GetAnimationArray(const int& index)
	{
		if (runSprites.empty())
		{
			runSprites.push_back(TexturesManager::getTexture(101));
			runSprites.push_back(TexturesManager::getTexture(102));
			runSprites.push_back(TexturesManager::getTexture(103));
		}

		if (actionSprites.empty())
		{
			actionSprites.push_back(TexturesManager::getTexture(104));
			actionSprites.push_back(TexturesManager::getTexture(105));
			actionSprites.push_back(TexturesManager::getTexture(106));
		}

		switch (index)
		{
		case 0:
			return runSprites;
			break;
		case 1:
			return actionSprites;
			break;
		}
	}

private:
	std::vector<sf::Texture> actionSprites;
	std::vector<sf::Texture> runSprites;
};