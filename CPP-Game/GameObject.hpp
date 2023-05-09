#pragma once

#include "Entity.hpp"
#include "Textures.hpp";
#include "Maths/Vector2.h";
#include "EntityManager.hpp";
#include "TransformComponent.hpp";
#include "SpriteRendererComponent.hpp";

class GameObject : public Entity
{
	sf::Texture tex = Textures::getTexture(1);
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(tex);

	GameObject(EntityManager* EM) {
		EM->CreateEntity("GameObject", this);
		RegisterComponents(EM);
	};

	void RegisterComponents(EntityManager* EM) {
		EM->CreateComponent("Transform", transformComponent);
		EM->AddComponent(this, transformComponent);
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
	};
};