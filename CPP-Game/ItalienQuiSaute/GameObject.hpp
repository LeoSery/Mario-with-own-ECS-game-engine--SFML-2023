#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "EntityManager.hpp"
#include "Textures.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

class GameObject : public Entity
{
public:
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent;
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());

	GameObject(EntityManager* EM, sf::Texture objTexture, Vector2<int> worldpos) {

		spriteRendererComponent = new SpriteRendererComponent(objTexture);
		spriteRendererComponent->setBlockPosition(worldpos);

		EM->CreateEntity("GameObject", this);
		RegisterComponents(EM);

		

		Tag = "GAMEOBJECT";
	};

	void RegisterComponents(EntityManager* EM) {
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
		EM->CreateComponent("Collider", colliderComponent);
		EM->AddComponent(this, colliderComponent);
	};
};