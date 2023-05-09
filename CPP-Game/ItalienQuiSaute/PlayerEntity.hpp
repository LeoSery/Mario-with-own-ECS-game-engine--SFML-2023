#pragma once

#include "Maths/Vector2.h";
#include "PlayerControllerComponent.hpp";
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";
#include "Textures.hpp";
#include "EntityManager.hpp";
#include "GravityComponent.hpp";

class PlayerEntity : public Entity
{
public:
	sf::Texture tex = Textures::getTexture(1);
	PlayerControllerComponent* playerControllerComponent = new PlayerControllerComponent();
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);
	PlayerEntity(EntityManager* EM) {
		EM->CreateEntity("Player", this);
		RegisterComponents(EM);
	};

	void RegisterComponents(EntityManager* EM) {
		EM->CreateComponent("PlayerController", playerControllerComponent);
		EM->AddComponent(this, playerControllerComponent);
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
	};

	void Move(Vector2<float> moveDirection, sf::Time deltaTime) {
		playerControllerComponent->Move(moveDirection);
		transformComponent->position += gravityComponent->ApplyGravity(playerControllerComponent->getDirectionVector(), deltaTime.asMicroseconds());
		spriteRendererComponent->setPosition(transformComponent->position);
	};
};