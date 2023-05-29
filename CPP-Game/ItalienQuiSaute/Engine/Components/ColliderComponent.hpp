#pragma once

#include "../../Engine/System/Libraries/Maths/Vector2.h";
#include "Component.hpp";

#include <SFML/Graphics.hpp>

class ColliderComponent : public Component
{
public:
	bool collided;
	std::vector<std::string> activeDirections;

	ColliderComponent(sf::Sprite* entitySprite)
	{
		this->entitySprite = entitySprite;
		Tag = "COLLIDER";
		collided = false;

	}

	//Check collisions using sprites hitboxes
	bool Collision(sf::Sprite* otherSprite)
	{
		std::string direction;
		sf::FloatRect entityHitbox = entitySprite->getGlobalBounds();
		sf::FloatRect otherHitbox = otherSprite->getGlobalBounds();

		if (entityHitbox.intersects(otherHitbox))
		{
			//Top Limit Diff
			if (((entityHitbox.top + entityHitbox.height) - otherHitbox.top) <= 30)
				direction = "FLOOR"; //if diff is between 30 pixel

			//Bot Limit Diff
			else if ((entityHitbox.top - (otherHitbox.top + otherHitbox.height)) >= -30)
				direction = "TOP"; //if diff is between 30 pixel

			//Left Limit Diff
			else if (((entityHitbox.left + entityHitbox.width) - otherHitbox.left) <= 30)
				direction = "LEFT"; //if diff is between 30 pixel

			//Right Limit Diff
			else if ((entityHitbox.left - (otherHitbox.left + otherHitbox.width)) >= -30)
				direction = "RIGHT"; //if diff is between 30 pixel

			activeDirections.push_back(direction);
			collided = true;
			return true;
		}
		direction = "ALL";
		collided = false;
		return false;
	}
private:
	sf::Sprite* entitySprite;
};