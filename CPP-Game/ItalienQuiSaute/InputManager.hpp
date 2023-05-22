#pragma once

#include <SFML/Graphics.hpp>
#include "Maths/Vector2.h"

class InputManager
{
public:
	InputManager(sf::Event _currentEvent)
	{
		currentEvent = _currentEvent;
		direction = { 0.0f,0.0f };
	}

	void UpdateEvent(sf::Event& _currentEvent)
	{
		currentEvent = _currentEvent;
	}

	Vector2<float> GetDirection()
	{
		Vector2<float> direction(0.0f, 0.0f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			direction.x = -1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			direction.x = 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			direction.y = -10.0f;
		}

		return direction;
	}
private:
	sf::Event currentEvent;
	Vector2<float> direction;
};