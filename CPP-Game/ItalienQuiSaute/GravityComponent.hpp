#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";

class GravityComponent : public Component
{
public:
	GravityComponent()
	{
		gravityStrength = 9.81f;
	}

	Vector2<float> ApplyGravity(Vector2<float> entityDirection, float deltaTime)
	{
		Vector2<float> gravityDirection(0.0f, gravityStrength);
		Vector2<float> velocity = entityDirection + gravityDirection / deltaTime;
		return velocity;
	}
private:
	float gravityStrength;
};