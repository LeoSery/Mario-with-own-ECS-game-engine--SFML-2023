#pragma once

#include "../../Engine/System/Managers/InputManager.hpp";
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

		//Move on X axis
		playerDirection.x = (moveDirection.x * speed * deltatime);

		//if there's y axis input and entity is not jumping
		if (moveDirection.y < 0.0f && !jumping) { 

			jump = moveDirection.y * deltatime /5;
			jumping = true;

		}
		//During a jump make the jump vector closer to 0
		if (jump < 0.0f && jumping) { 
			jump += (jumpspeed * 1 / 100) * deltatime;
			playerDirection.y = (jump);

		}
		else
		{
			jump = 0.0f;
		}



	}


	Vector2<float> getDirectionVector() {
		return playerDirection;
	}

	//Used with collisions (TODO: with states)
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

	//Used to bounce on ennemies when killed (double jump)
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