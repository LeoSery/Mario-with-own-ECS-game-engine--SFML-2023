#pragma once

#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "Textures.hpp"
#include "Entity.hpp"

class GameObject : public Entity
{
public:
	sf::Texture playerTexture = Textures::getTexture(1);
	TransformComponent* transformComponent = new TransformComponent();
	SpriteRendererComponent* spriteRendererComponent = new SpriteRendererComponent(playerTexture);

	GameObject()

private
};