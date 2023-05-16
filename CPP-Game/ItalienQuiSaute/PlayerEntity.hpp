#pragma once

#include "Maths/Vector2.h";
#include "PlayerControllerComponent.hpp";
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";
#include "ColliderComponent.hpp";
#include "Textures.hpp";
#include "EntityManager.hpp";
#include "GravityComponent.hpp";
#include "CameraComponent.hpp";


class PlayerEntity : public Entity
{
public:

	sf::Texture tex = Textures::getTexture(1);
	PlayerControllerComponent* playerControllerComponent = new PlayerControllerComponent();
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());
	HealthComponent* healthComponent = new HealthComponent();
	CameraComponent* cameraComponent;

	PlayerEntity(EntityManager* EM, sf::RenderWindow& window) {
		EM->CreateEntity("Player", this);


		cameraComponent = new CameraComponent(window, transformComponent->position);

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
	};

	void Move(Vector2<float> moveDirection, sf::Time deltaTime, sf::RenderWindow& window)
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

		cameraComponent->Move(newpos, window);

		colliderComponent->activeDirections.clear();
		spriteRendererComponent->setPosition(transformComponent->nextpos);
	};
};