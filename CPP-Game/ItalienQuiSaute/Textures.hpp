#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Textures {
public:


	static sf::Texture getTexture(const int& texEnum) {
		switch (texEnum)
		{
		case 0:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 1:
			return loadTexture("Assets/Sprites/rat.png");
			break;
		case 2:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 3:
			return loadTexture("Assets/Sprites/brick.png");
			break;
		case 4:
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