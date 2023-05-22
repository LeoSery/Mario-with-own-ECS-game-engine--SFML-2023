#pragma once

#include <SFML/Graphics.hpp>
#include "Component.hpp";

class PlayerStateComponent : public Component
{
public:
	PlayerStateComponent()
	{
		currentMovementState = movementState::IDLE;
	}

private:
	enum class movementState { WALK, JUMP, IDLE, VICTORY };
	movementState currentMovementState;
};