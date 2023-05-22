#pragma once

#include "Inputmanager.hpp";
#include "Component.hpp";
#include <string>

class PlayerControllerComponent : public Component
{
public:
	
	PlayerControllerComponent()
	{
		speed = 0.8f;
		jumpspeed = 1.0f;
		jump = 0.0f;
		playerDirection = { 0.0f, 0.0f };
	}

	void Move(Vector2<float> moveDirection, float deltatime)
	{


		playerDirection.x = (moveDirection.x *speed * deltatime);
		
		if (moveDirection.y < 0.0f && !jumping) {
			jump = moveDirection.y;
			jumping = true;

		}
		if (jump < 0.0f && jumping) { 
			jump += (jumpspeed * 1 / 100)*deltatime;
			playerDirection.y = (jump);
			
		}
		else
		{
			jump = 0.0f;
		}

		std::cout << playerDirection.y << "\n";
		

		
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
			playerDirection.y = 0.0f;
			jump = 0.0f;
		}
	}

	void setFalling() {
		playerDirection.y = 0.0f;
		jump = 0.0f;
	}

	void addJump(float height) {
		jumping = true;
		jump -= height;
	}
private:
	bool jumping = false;
	float speed;
	float jumpspeed;
	float jump;
	Vector2<float> playerDirection;
};