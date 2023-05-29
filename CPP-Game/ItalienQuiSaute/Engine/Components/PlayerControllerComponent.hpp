#pragma once

#include "../../Engine/System/Managers/InputManager.hpp";
#include "Component.hpp";

#include <iostream>
#include <string>

class PlayerControllerComponent : public Component
{
public:
	PlayerControllerComponent()
	{
		speed = 700.0f;
		jumptime = 0.0f;
		jumpforce = -2000.0f; //get overwriten, to change it go to InputManager
		playerDirection = { 0.0f, 0.0f };

	}

	void Move(Vector2<float> moveDirection, float deltatime)
	{
		//Move on X axis
		playerDirection.x = (moveDirection.x * speed * deltatime);

		//if there's y axis input and entity is not jumping
		if (moveDirection.y < 0.0f && !jumping)
		{
			jumpforce = moveDirection.y;
			jumptime = 1.0f;
			jumping = true;

		}

		//During a jump make the jump air time closer to 0
		if (jumptime > 0.0f && jumping)
		{
			jumptime -= deltatime;
			playerDirection.y = jumpforce * deltatime * jumptime;
		}
		else
			playerDirection.y = 0.0f;
	}


	Vector2<float> getDirectionVector()
	{
		return playerDirection;
	}

	//Used with collisions (TODO: with states)
	void setJumping(bool cond)
	{
		if (cond)
			jumping = true;
		else
		{
			jumping = false;
			playerDirection.y = 0.0f;
			jumptime = 0.0f;
		}
	}

	void setFalling()
	{
		playerDirection.y = 0.0f;
		jumptime = 0.0f;
	}

	//Used to bounce on ennemies when killed (double jump)
	void addJump(float timejumping)
	{
		jumping = true;
		jumptime = timejumping;
	}

private:
	Vector2<float> playerDirection;
	bool jumping = false;
	float jumpforce;
	float jumptime;
	float speed;
};