#pragma once

#include "Maths/Vector2.h";
#include "PlayerControllerComponent.hpp";
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";
#include "ColliderComponent.hpp";
#include "TexturesManager.hpp";
#include "EntityManager.hpp";
#include "GravityComponent.hpp";
#include "CameraComponent.hpp";
#include "PlayerStateComponent.hpp";


class PlayerEntity : public Entity
{
public:

	sf::Texture tex = TexturesManager::getTexture(101);
	PlayerControllerComponent* playerControllerComponent = new PlayerControllerComponent();
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());
	PlayerStateComponent* playerStateComponent = new PlayerStateComponent();
	HealthComponent* healthComponent = new HealthComponent();
	CameraComponent* cameraComponent;

	PlayerEntity(EntityManager* EM, sf::RenderWindow& window, Vector2<int> mapDimensions, Vector2<float> startpos) {
		EM->CreateEntity("Player", this);


		transformComponent->position = startpos;
		transformComponent->nextpos = startpos;
		cameraComponent = new CameraComponent(window, transformComponent->position, mapDimensions);

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
		EM->CreateComponent("Gravity", gravityComponent);
		EM->AddComponent(this, gravityComponent);
		EM->CreateComponent("Camera", cameraComponent);
		EM->AddComponent(this, cameraComponent);
		EM->CreateComponent("Health", healthComponent);
		EM->AddComponent(this, healthComponent);
		EM->CreateComponent("PlayerState", playerStateComponent);
		EM->AddComponent(this, playerControllerComponent);
	};

	void Move(Vector2<float> moveDirection, sf::Time deltaTime, sf::RenderWindow& window, Background* bg)
	{
		if (std::find(colliderComponent->activeDirections.begin(), colliderComponent->activeDirections.end(), "FLOOR") != colliderComponent->activeDirections.end()) {
			playerControllerComponent->setJumping(false);

		}
		else
		{
			playerControllerComponent->setJumping(true);
		}



		playerControllerComponent->Move(moveDirection, deltaTime.asMilliseconds());
		Vector2<float> newpos = playerControllerComponent->getDirectionVector();


		newpos = gravityComponent->ApplyGravity(newpos, deltaTime.asMicroseconds());

		newpos = transformComponent->addPos(newpos, colliderComponent->activeDirections);

		cameraComponent->Move(spriteRendererComponent->getSprite()->getPosition(), newpos, window, bg);

		colliderComponent->activeDirections.clear();
		spriteRendererComponent->setPosition(transformComponent->nextpos);
	};
};