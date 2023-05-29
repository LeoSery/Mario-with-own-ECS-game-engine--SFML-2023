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
		case 1:
			return loadTexture("Game/Assets/Sprites/Map/ground.png");
			break;
		case 2:
			return loadTexture("Game/Assets/Sprites/Map/brick.png");
			break;
		case 3:
			break;
		case 4:
			return loadTexture("Game/Assets/Sprites/Map/flag_1.png");
			break;
		case 5:
			return loadTexture("Game/Assets/Sprites/Map/flag_2.png");
			break;
		case 6:
			return loadTexture("Game/Assets/Sprites/Enemies/goomba.png");
			break;
		case 7:
			return loadTexture("Game/Assets/Sprites/Map/super_block.png");
			break;
		case 8:
			return loadTexture("Game/Assets/Sprites/Map/background.png");
			break;
		case 101:
			return loadTexture("Game/Assets/Sprites/Character/mario_walk_1.png");
			break;
		case 102:
			return loadTexture("Game/Assets/Sprites/Character/mario_walk_2.png");
			break;
		case 103:
			return loadTexture("Game/Assets/Sprites/Character/mario_walk_3.png");
			break;
		case 104:
			return loadTexture("Game/Assets/Sprites/Character/mario_win.png");
			break;
		case 105:
			return loadTexture("Game/Assets/Sprites/Character/mario_idle.png");
			break;
		case 106:
			return loadTexture("Game/Assets/Sprites/Character/mario_jump.png");
			break;
		default:
			break;
		}
	}

	static sf::Texture loadTexture(const std::string& filename)
	{
		sf::Texture texture;
		if (!texture.loadFromFile(filename))
			std::cerr << "Failed to load texture from file " << filename << std::endl;
		return texture;
	}

	void resizeSprite(sf::Sprite& sprite, int cellSize)
	{
		float scaleFactor = cellSize / std::max(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
		sprite.setScale(scaleFactor, scaleFactor);
	}
};