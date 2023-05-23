#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "GravityComponent.hpp"
#include "TexturesManager.hpp"
#include "Maths/Vector2.h"
#include "Entity.hpp"
#include "EntityManager.hpp"

class Flag : public Entity
{
public:
	sf::Texture flagTexture;
	SpriteRendererComponent* spriteRendererComponent;
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());

	Flag(EntityManager* EM, Vector2<int> startPos, int texture)
	{
		
		flagTexture = TexturesManager::getTexture(texture);
		spriteRendererComponent = new SpriteRendererComponent(flagTexture);
		EM->CreateEntity("Flag", this);

		RegisterComponents(EM);
		spriteRendererComponent->setBlockPosition(startPos);
		std::cout << "Construct > Pos x : " << startPos.x << "Pos y : " << startPos.y << std::endl;
		Tag = "FLAG";
	}

	void RegisterComponents(EntityManager* EM)
	{
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
		EM->CreateComponent("Collider", colliderComponent);
		EM->AddComponent(this, colliderComponent);

	}

	void Move(sf::Time deltaTime)
	{
		colliderComponent->activeDirections.clear();
	}

};