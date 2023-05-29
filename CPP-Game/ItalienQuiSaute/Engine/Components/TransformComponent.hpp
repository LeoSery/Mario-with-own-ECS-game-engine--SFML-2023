#pragma once

#include "../../Engine/System/Libraries/Maths/Vector2.h"
#include "Component.hpp"

class TransformComponent : public Component
{
public:

	Vector2<float> rotation;
	Vector2<float> position;
	Vector2<float> nextpos;
	Vector2<float> scale;

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
		nextpos = _position;
		rotation = _rotation;
		scale = _scale;
	}

	Vector2<float> addPos(Vector2<float> _position, std::vector<std::string> directions)
	{
		position = nextpos;

		//Check collisions
		for (std::string direction : directions)
		{
			if (direction == "LEFT")
			{
				if (_position.x > 0.0f)
					_position.x = 0.0f;
			}

			else if (direction == "RIGHT")
			{
				if (_position.x < 0.0f)
					_position.x = 0.0f;
			}

			else if (direction == "FLOOR")
			{
				if (_position.y > 0.0f)
					_position.y = 0.0f;
			}

			else if (direction == "TOP")
			{
				if (_position.y < 0.0f)
					_position.y = 0.0f;
			}
		}
		nextpos += _position;
		return _position;
	}
};