#pragma once

#include "../../Engine/System/Managers/TexturesManager.hpp"
#include "../../Engine/System/Managers/EntityManager.hpp"
#include "../../Engine/System/Libraries/Maths/Vector2.h"
#include "../Components/SpriteRendererComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ColliderComponent.hpp"
#include "../Components/GravityComponent.hpp"
#include "Entity.hpp"

class Flag : public Entity
{
public:
	sf::Texture flagTexture;
	SpriteRendererComponent* spriteRendererComponent;
	ColliderComponent* colliderComponent = new ColliderComponent(spriteRendererComponent->getSprite());

	//GameObject with only Sprite and Collider
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
};