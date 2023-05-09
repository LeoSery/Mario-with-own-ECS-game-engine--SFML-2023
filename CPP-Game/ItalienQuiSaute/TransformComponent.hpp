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

	void addPos(Vector2<float> _position, std::vector<std::string> directions) {

		
		position = nextpos;
		bool side = false;
		for(std::string direction : directions)
		{
			 if (direction == "SIDE") {
				 _position.x = 0.0f;
				 side = true;
			}

			else if (direction == "FLOOR") {
				if (_position.y > 0.0f && !side) {
					_position.y = 0.0f;
				}
			}
			else if (direction == "TOP")
			{
				if (_position.y < 0.0f) {
					_position.y = 0.0f;
				}

			}
		}

		nextpos += _position;
		
		

	}
	Vector2<float> nextpos;
	Vector2<float> position;
	Vector2<float> rotation;
	Vector2<float> scale;
};