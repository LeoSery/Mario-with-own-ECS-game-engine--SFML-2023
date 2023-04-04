#pragma once

#include "Inputmanager.hpp";
#include "Entity.hpp";

class PlayerControllerComponent : Entity
{
public:
	PlayerControllerComponent()
	{
		speed = 0.0f;
		playerDirection = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection)
	{
		playerDirection = moveDirection;
	}

private:
	float speed;
	Vector2<float> playerDirection;
};