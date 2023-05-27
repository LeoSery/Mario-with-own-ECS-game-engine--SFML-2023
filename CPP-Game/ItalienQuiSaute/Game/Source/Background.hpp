#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "ColliderComponent.hpp"
#include "TexturesManager.hpp"
#include "EntityManager.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

class Background : public Entity
{
public:
	SpriteRendererComponent* spriteRendererComponent;

	Background(EntityManager* EM, sf::Texture objTexture, Vector2<int> worldpos, float Z = 2.0f) {

		depth = Z;

		spriteRendererComponent = new SpriteRendererComponent(objTexture);
		spriteRendererComponent->setBlockPosition(worldpos);


		EM->CreateEntity("Background", this);
		RegisterComponents(EM);



		Tag = "BACKGROUND";
	};

	void RegisterComponents(EntityManager* EM) {
		EM->CreateComponent("SpriteRenderer", spriteRendererComponent);
		EM->AddComponent(this, spriteRendererComponent);
	};


	void Move(Vector2<float> move) {
		Vector2<float> pos = (move/depth) + spriteRendererComponent->getPosition();
		spriteRendererComponent->setPosition(pos);
	}

private:
	float depth;
};