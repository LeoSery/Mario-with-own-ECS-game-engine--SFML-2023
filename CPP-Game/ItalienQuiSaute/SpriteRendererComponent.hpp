#pragma once

#include "Component.hpp"
#include "Maths/Vector2.h"
#include <SFML/Graphics.hpp>

class SpriteRendererComponent : public Component
{
public:
	SpriteRendererComponent(sf::Texture& tex) : Component(0, "default") {
		Tag = "SPRITE_RENDERER";
		this->tex = tex;
		this->sprite = loadSprite();
		pos = sf::Vector2f(0, 0);
		width = 64;
	};

	sf::Sprite loadSprite() {
		sprite.setTexture(tex);
		sprite.setPosition(pos);
		return sprite;
	}

	Vector2<float> getPosition() {
		return { sprite.getPosition().x, sprite.getPosition().y };
	}

	sf::Sprite* getSprite() {
		return &sprite;
	}

	void setPosition(Vector2<float> worldpos) {
		pos = sf::Vector2f(worldpos.x, worldpos.y);
	}

	

	void setBlockPosition(Vector2<int> worldpos) {
		pos = sf::Vector2f(worldpos.x * width, worldpos.y * width);
	}

	void UpdateAnimation(std::vector<sf::Texture> animationsTextures, sf::Time deltaTime)
	{
		time += deltaTime;
		if (time.asMilliseconds() > 200)
		{
			tick = 0;
			sprite.setTexture(animationsTextures[currentAnimationIndex + 1]);
			currentAnimationIndex++;
		}
		tick++;
	}

private:
	int tick;
	int width;
	int currentAnimationIndex;
	sf::Time time;
	sf::Vector2f pos;
	sf::Texture tex;
	sf::Sprite sprite;
};