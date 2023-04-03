#pragma once


#include "Component.hpp"
#include <SFML/Graphics.hpp>



class SpriteRendererComponent : public Component 
{
public:
	SpriteRendererComponent(sf::Texture& tex) : Component(0, "default") {

		this->tex = tex;
		this->sprite = loadSprite();


	};

	sf::Sprite loadSprite() {
		sprite.setTexture(tex);
		return sprite;
	}
	

private:
	sf::Texture tex;
	sf::Sprite sprite;
	
};