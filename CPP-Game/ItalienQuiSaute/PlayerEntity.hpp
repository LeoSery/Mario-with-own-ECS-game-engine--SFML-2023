#pragma once

#include "Maths/Vector2.h";
#include "PlayerControllerComponent.hpp";
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";
#include "ColliderComponent.hpp"
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
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());

	PlayerEntity(EntityManager* EM) {
		EM->CreateEntity("Player", this);
		RegisterComponents(EM);

		Tag = "PLAYER";
	};


	void RegisterComponents(EntityManager* EM) {
		EM->CreateComponent("PlayerController", playerControllerComponent);
		EM->AddComponent(this, playerControllerComponent);
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
		EM->CreateComponent("Collider", colliderComponent);
		EM->AddComponent(this, colliderComponent);
	};

	void Move(Vector2<float> moveDirection, sf::Time deltaTime) {



		playerControllerComponent->Move(moveDirection, deltaTime.asMilliseconds());
		Vector2<float> newpos = playerControllerComponent->getDirectionVector();


		newpos = gravityComponent->ApplyGravity(playerControllerComponent->getDirectionVector(), deltaTime.asMicroseconds());

		transformComponent->addPos(newpos, colliderComponent->activeDirections);
		colliderComponent->activeDirections.clear();
		spriteRendererComponent->setPosition(transformComponent->nextpos);
		

	};


	




};