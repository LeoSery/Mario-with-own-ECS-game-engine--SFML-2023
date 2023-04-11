#pragma once

#include "Inputmanager.hpp";
#include "Component.hpp";
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


	Vector2<float> getDirectionVector() {
		return playerDirection;
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