#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "GravityComponent.hpp"
#include "TexturesManager.hpp"
#include "Maths/Vector2.h"
#include "Entity.hpp"

class Enemy : public Entity
{
public:
	sf::Texture playerTexture = TexturesManager::getTexture(6);
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(playerTexture);
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());
	HealthComponent* healthComponent = new HealthComponent();

	Enemy(EntityManager* EM, Vector2<float> startPos)
	{
		EM->CreateEntity("Enemy", this);
		speed = 1.0f;
		direction = { 1.0f, 0.0f };

		RegisterComponents(EM);
		transformComponent->position = startPos;
		transformComponent->nextpos = startPos;
		std::cout << "Construct > Pos x : " << startPos.x << "Pos y : " << startPos.y << std::endl;
		Tag = "ENEMY";
	}

	void RegisterComponents(EntityManager* EM)
	{
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
		EM->CreateComponent("Collider", colliderComponent);
		EM->AddComponent(this, colliderComponent);
		EM->CreateComponent("Gravity", gravityComponent);
		EM->AddComponent(this, gravityComponent);
		EM->CreateComponent("Health", healthComponent);
		EM->AddComponent(this, healthComponent);
	}

	void Move(sf::Time deltaTime)
	{
		if (std::find(colliderComponent->activeDirections.begin(), colliderComponent->activeDirections.end(), "LEFT") != colliderComponent->activeDirections.end())
		{
			direction = -direction;
		}
		else if (std::find(colliderComponent->activeDirections.begin(), colliderComponent->activeDirections.end(), "RIGHT") != colliderComponent->activeDirections.end())
		{
			direction = -direction;
		}

		Vector2<float> newpos = direction;

		newpos = gravityComponent->ApplyGravity(newpos, deltaTime.asMicroseconds());

		transformComponent->addPos(newpos, colliderComponent->activeDirections);
		colliderComponent->activeDirections.clear();
		spriteRendererComponent->setPosition(transformComponent->nextpos);
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