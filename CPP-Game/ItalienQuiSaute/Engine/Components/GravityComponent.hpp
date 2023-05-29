#pragma once

#include "../../Engine/System/Libraries/Maths/Vector2.h";
#include "Component.hpp";

class GravityComponent : public Component
{
public:
	GravityComponent()
	{
		gravityStrength = 9.81f;
		mass = 1.7f;
	}

	//Apply Gravity to a direction vector
	Vector2<float> ApplyGravity(Vector2<float> entityDirection, float deltaTime)
	{
		Vector2<float> gravityDirection(0.0f, gravityStrength);
		Vector2<float> velocity = entityDirection + gravityDirection * (deltaTime / 20000) * mass;
		return velocity;
	}

private:
	float gravityStrength;
	float mass;
};