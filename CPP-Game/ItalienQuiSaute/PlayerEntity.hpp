#pragma once

#include "Maths/Vector2.h";
#include "PlayerControllerComponent.hpp";
#include "GravityComponent.hpp"
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";
#include "Textures.hpp";
#include "EntityManager.hpp"


class PlayerEntity : public Entity
{
public:
	sf::Texture tex = Textures::getTexture(1);
	PlayerControllerComponent* playerControllerComponent = new PlayerControllerComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);
	GravityComponent* gravityComponent = new GravityComponent();

	PlayerEntity(EntityManager* EM)
	{
		EM->CreateEntity("Player", this);
		RegisterComponents(EM);
	};

	void RegisterComponents(EntityManager* EM)
	{
		EM->CreateComponent("PlayerController", playerControllerComponent);
		EM->AddComponent(this, playerControllerComponent);
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
	};

	void Move(Vector2<float> moveDirection, sf::Time deltaTime)
	{
		//playerControllerComponent->Move(moveDirection);
		//transformComponent->position += playerControllerComponent->getDirectionVector();
		//spriteRendererComponent->setPosition(transformComponent->position);

		transformComponent->position += gravityComponent->ApplyGravity(moveDirection, deltaTime.asMicroseconds());
	};
};
