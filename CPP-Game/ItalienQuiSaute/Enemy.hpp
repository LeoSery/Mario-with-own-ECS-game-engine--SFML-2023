#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "Maths/Vector2.h"
#include "Textures.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
public:
	sf::Texture playerTexture = Textures::getTexture(1);
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(playerTexture);

	Enemy()
	{
		speed = 1.0f;
		direction = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection)
	{
		transformComponent->position += moveDirection;
		spriteRendererComponent->setPosition(transformComponent->position);
	}

	float GetSpeed()
	{
		return speed;
	}

	Vector2<float> GetDirection()
	{
		return direction;
	}

	void SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	void SetDirection(Vector2<float> newDirection)
	{
		direction = newDirection;
	}
private:
	float speed;
	Vector2<float> direction;
};