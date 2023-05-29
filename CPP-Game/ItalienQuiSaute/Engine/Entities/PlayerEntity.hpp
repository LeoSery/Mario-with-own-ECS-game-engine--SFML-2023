#pragma once

#include "../../Engine/System/Managers/TexturesManager.hpp";
#include "../../Engine/System/Managers/EntityManager.hpp";
#include "../../Engine/System/Libraries/Maths/Vector2.h";
#include "../Components/PlayerControllerComponent.hpp";
#include "../Components/SpriteRendererComponent.hpp";
#include "../Components/TransformComponent.hpp";
#include "../Components/ColliderComponent.hpp";
#include "../Components/GravityComponent.hpp";
#include "../Components/CameraComponent.hpp";


class PlayerEntity : public Entity
{
public:

	sf::Texture tex = TexturesManager::getTexture(101);
	PlayerControllerComponent* playerControllerComponent = new PlayerControllerComponent();
	GravityComponent* gravityComponent = new GravityComponent();
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());
	HealthComponent* healthComponent = new HealthComponent();
	CameraComponent* cameraComponent;

	PlayerEntity(EntityManager* EM, sf::RenderWindow& window, Vector2<int> mapDimensions, Vector2<float> startpos)
	{
		EM->CreateEntity("Player", this);
		transformComponent->position = startpos;
		transformComponent->nextpos = startpos;
		cameraComponent = new CameraComponent(window, transformComponent->position, mapDimensions);
		RegisterComponents(EM);
		Tag = "PLAYER";
	};

	void RegisterComponents(EntityManager* EM)
	{
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

	void Move(Vector2<float> moveDirection, sf::Time deltaTime, sf::RenderWindow& window, Background* bg)
	{
		//check collisions
		if (std::find(colliderComponent->activeDirections.begin(), colliderComponent->activeDirections.end(), "FLOOR") != colliderComponent->activeDirections.end())
			playerControllerComponent->setJumping(false);
		else if (std::find(colliderComponent->activeDirections.begin(), colliderComponent->activeDirections.end(), "TOP") != colliderComponent->activeDirections.end())
			playerControllerComponent->setFalling();
		else
			playerControllerComponent->setJumping(true);

		//Add to pos direction vector
		playerControllerComponent->Move(moveDirection, deltaTime.asSeconds());
		Vector2<float> newpos = playerControllerComponent->getDirectionVector();
		newpos = gravityComponent->ApplyGravity(newpos, deltaTime.asMicroseconds());
		newpos = transformComponent->addPos(newpos, colliderComponent->activeDirections);
		cameraComponent->Move(spriteRendererComponent->getSprite()->getPosition(), newpos, window, bg);
		colliderComponent->activeDirections.clear();
		spriteRendererComponent->setPosition(transformComponent->nextpos);
	};
};