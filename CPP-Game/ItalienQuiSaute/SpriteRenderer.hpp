#pragma once


#include "Component.hpp"
#include <SFML/Graphics.hpp>



class SpriteRenderer : public Component 
{
public:
	SpriteRenderer(std::uint32_t UUID, std::string Name, sf::Texture& tex) : Component(UUID, Name) {

		this->tex = tex;
		this->sprite = loadSprite();


	};

	sf::Sprite* loadSprite() {
		sprite = new sf::Sprite;
		sprite->setTexture(tex);
		return sprite;
	}
	
	

private:
	sf::Texture tex;
	sf::Sprite* sprite;
};