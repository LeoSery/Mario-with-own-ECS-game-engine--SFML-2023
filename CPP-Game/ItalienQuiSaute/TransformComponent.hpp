#pragma once

#include "Component.hpp"
#include "Maths/Vector2.h"

class TransformComponent : public Component
{
public:
	TransformComponent()
	{
		position = { 0, 0 };
		rotation = { 0, 0 };
		scale = { 0, 0 };
		nextpos = position;
	}

	TransformComponent(Vector2<float> _position, Vector2<float> _rotation = { 0.0f, 0.0f }, Vector2<float> _scale = { 0.0f, 0.0f })
	{
		position = nextpos;
		nextpos =  _position ;
		rotation = _rotation;
		scale = _scale;
	}

	void addPos(Vector2<float> _position) {
		position = nextpos;
		nextpos +=  _position;
		//std::cout << "x: " << position.x << " y:" << position.y << "\n";
		std::cout << "nextpos: " << "x: " << nextpos.x << " y:" << nextpos.y << "\n";
	}
	Vector2<float> nextpos;
	Vector2<float> position;
	Vector2<float> rotation;
	Vector2<float> scale;
};