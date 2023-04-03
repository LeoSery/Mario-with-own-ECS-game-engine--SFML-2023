#pragma once

#include "Component.hpp"
#include "Maths/Vector2.h"

class TransformComponent : Component
{
public:
	TransformComponent()
	{
		position = { 0, 0 };
		rotation = { 0, 0 };
		scale = { 0, 0 };
	}

	TransformComponent(Vector2<float> _position, Vector2<float> _rotation = { 0.0f, 0.0f }, Vector2<float> _scale = { 0.0f, 0.0f })
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
	}
	Vector2<float> position;
	Vector2<float> rotation;
	Vector2<float> scale;
};