#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class TexturesManager
{
public:
	static sf::Texture getTexture(const int& texEnum)
	{
		switch (texEnum)
		{
		case 0:
			return loadTexture("Assets/Sprites/ground.png");
			break;
		case 1:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 2:
			return loadTexture("Assets/Sprites/mario_idle.png");
			break;
		case 3:
			return loadTexture("Assets/Sprites/goomba.png");
			break;
		case 5:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 6:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 7:
			return loadTexture("Assets/Sprites/background.png");
			break;
		case 8:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		default:
			break;
		}
	}

	static sf::Texture loadTexture(const std::string& filename)
	{
		sf::Texture texture;

		if (!texture.loadFromFile(filename)) {
			std::cerr << "Failed to load texture from file " << filename << std::endl;
		}

		return texture;
	}

	void resizeSprite(sf::Sprite& sprite, int cellSize)
	{
		float scaleFactor = cellSize / std::max(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		sprite.setScale(scaleFactor, scaleFactor);
	}
};