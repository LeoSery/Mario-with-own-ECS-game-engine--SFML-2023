#pragma once

#include "Inputmanager.hpp";
#include "Component.hpp";
#include <string>

class PlayerControllerComponent : public Component
{
public:
	
	PlayerControllerComponent()
	{
		speed = 1.0f;
		jump = 0.0f;
		playerDirection = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection, float deltatime)
	{

		playerDirection.x = (moveDirection.x * deltatime);
		
		if (moveDirection.y < 0.0f && !jumping) {
			jump += moveDirection.y *deltatime;
			jumping = true;

		}
		if (jump < 0.0f && jumping) {
			playerDirection.y = (jump);
			jump += (speed * 1 / 100);
		}
		else
		{
			jump = 0.0f;
		}

		

		
	}


	Vector2<float> getDirectionVector() {
		return playerDirection;
	}

	void setJumping(bool cond) {
		if (cond) {
			jumping = true;
		}
		else {
			jumping = false;
			jump = 0.0f;
		}
	}

private:
	bool jumping = false;
	float speed;
	float jump;
	Vector2<float> playerDirection;
};