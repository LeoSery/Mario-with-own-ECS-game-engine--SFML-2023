#pragma once

#include "../../Engine/System/Managers/InputManager.hpp";
#include "Component.hpp";

#include <string>
#include <iostream>

class PlayerControllerComponent : public Component
{
public:

	PlayerControllerComponent()
	{
		speed = 700.0f;
		jumptime = 0.0f;
		jumpforce = -5.0f;
		playerDirection = { 0.0f, 0.0f };
		
	}


	void Move(Vector2<float> moveDirection, float deltatime)
	{

		//Move on X axis
		playerDirection.x = (moveDirection.x * speed * deltatime);

		//if there's y axis input and entity is not jumping
		if (moveDirection.y < 0.0f && !jumping) { 
			jumpforce = moveDirection.y;
			jumptime = 1.0f;
			jumping = true;

		}
		//During a jump make the jump air time closer to 0
		if (jumptime > 0.0f && jumping) { 
			jumptime -= deltatime;
			
			playerDirection.y = jumpforce*deltatime*jumptime;

		}
		else {
			jumping = false;
			playerDirection.y = 0.0f;
		}
		std::cout << jumptime << "\n";

		


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
			jumptime = 0.0f;
		}
	}

	void setFalling() {
		playerDirection.y = 0.0f;
		jumptime = 0.0f;
	}

	//Used to bounce on ennemies when killed (double jump)
	void addJump(float timejumping) {
		jumping = true;
		jumptime = timejumping;
		
		
	}
private:
	bool jumping = false;
	float speed;
	float jumptime;
	float jumpforce;
	Vector2<float> playerDirection;
};