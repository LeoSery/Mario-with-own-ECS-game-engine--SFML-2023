#pragma once

#include "Inputmanager.hpp";
#include "Component.hpp";
#include <string>

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent()
	{
		speed = 0.5f;
		jump = 0.0f;
		playerDirection = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection, float deltatime)
	{
		
		if (moveDirection.y < 0.0f && jump >= 0.0f) {
			jump += moveDirection.y *deltatime;

		}
		if (jump < 0.0f) {
			playerDirection.y = (jump);
			std::cout << jump << "\n";
			jump += (speed * 1 / 100);
			std::cout << jump << "\n";
		}

		playerDirection.x = (moveDirection.x * deltatime);

		
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
	float jump;
	Vector2<float> playerDirection;
};