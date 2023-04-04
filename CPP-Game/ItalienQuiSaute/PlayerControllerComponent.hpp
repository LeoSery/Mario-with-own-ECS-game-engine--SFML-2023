#pragma once

#include "Inputmanager.hpp";
#include "Entity.hpp";
#include <string>

class PlayerControllerComponent : public Component
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

	//debug func
	int GetDirectionX()
	{
		return playerDirection.x;
	}

	int GetDirectionY()
	{
		return playerDirection.y;
	}

private:
	float speed;
	Vector2<float> playerDirection;
};