#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";
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

	bool Collision(sf::Sprite* otherSprite)
	{
		std::string direction;
		sf::FloatRect entityHitbox = entitySprite->getGlobalBounds();
		sf::FloatRect otherHitbox = otherSprite->getGlobalBounds();

		if (entityHitbox.intersects(otherHitbox)) {


			//Top Limit Diff
			if (((entityHitbox.top + entityHitbox.height) - otherHitbox.top) <= 3) { //if diff is between 3 pixel
				direction = "FLOOR";
			}

			//Bot Limit Diff
			else if ((entityHitbox.top - (otherHitbox.top + otherHitbox.height)) >= -3) { //if diff is between 3 pixel
				direction = "TOP";
			}

			//Left Limit Diff
			
			else if (((entityHitbox.left + entityHitbox.width) - otherHitbox.left) <= 3) { //if diff is between 3 pixel
				direction = "SIDE";
			}

			//Right Limit Diff

			else if ((entityHitbox.left - (otherHitbox.left+otherHitbox.width)) >= -3) { //if diff is between 3 pixel
				direction = "SIDE";
			}

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