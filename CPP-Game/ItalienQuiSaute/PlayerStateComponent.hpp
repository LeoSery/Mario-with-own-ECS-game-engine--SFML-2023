#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp";

enum class movementState { WALK, JUMP, IDLE, VICTORY };

class PlayerStateComponent : public Component
{
public:
	PlayerStateComponent()
	{
		Tag = "STATE";
		currentMovementState = movementState::IDLE;
	}

	void SetState(movementState newState)
	{
		currentMovementState = newState;
	}

	movementState GetState()
	{
		return currentMovementState;
	}

private:
	movementState currentMovementState;
};