#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";
#include <SFML/Graphics.hpp>

class ColliderComponent : public Component
{
public:
	bool collided;
	ColliderComponent(sf::Sprite* entitySprite)
	{
		this->entitySprite = entitySprite;
		Tag = "COLLIDER";
		collided = false;
	}

	bool Collision(sf::Sprite* otherSprite)
	{
		sf::FloatRect entityHitbox = entitySprite->getGlobalBounds();
		sf::FloatRect otherHitbox = otherSprite->getGlobalBounds();

		if (entityHitbox.intersects(otherHitbox)) {
			collided = true;
			return true;
		}
		
		collided = false;
		return false;
	}
private:
	
	sf::Sprite* entitySprite;
};