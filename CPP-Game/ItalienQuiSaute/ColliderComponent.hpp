#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";
#include <SFML/Graphics.hpp>

class ColliderComponent : public Component
{
public:
	ColliderComponent(sf::Sprite* entitySprite)
	{
		this->entitySprite = entitySprite;
		Tag = "COLLIDER";
	}

	bool Collision(sf::Sprite* otherSprite)
	{
		sf::FloatRect entityHitbox = entitySprite->getGlobalBounds();
		sf::FloatRect otherHitbox = otherSprite->getGlobalBounds();
		if (entityHitbox.intersects(otherHitbox)) {
			return true;
		}
		return false;
	}
private:
	sf::Sprite* entitySprite;
};