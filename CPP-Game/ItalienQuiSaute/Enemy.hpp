#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "GravityComponent.hpp"
#include "Maths/Vector2.h"
#include "Textures.hpp"
#include "Entity.hpp"

class Enemy : public Entity
{
public:
	sf::Texture playerTexture = Textures::getTexture(1);
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(playerTexture);

	Enemy()
	{
		speed = 1.0f;
		direction = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection, sf::Time deltaTime)
	{
		transformComponent->position += gravityComponent->ApplyGravity(moveDirection, deltaTime.asMicroseconds());
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