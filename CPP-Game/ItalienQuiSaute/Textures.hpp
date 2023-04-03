#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Textures {
public:
	sf::Texture loadTexture(const std::string& filename)
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