#pragma once

#include "Component.hpp";
#include "Maths/Vector2.h";
#include <SFML/Graphics.hpp>;

class CameraComponent : public Component
{
public:
	CameraComponent(sf::RenderWindow& window)
	{
		view.setCenter(sf::Vector2f(1000.f, 800.f));
		view.setSize(sf::Vector2f(400.f, 400.f));
		view.zoom(5.0f);
		window.setView(view);
	}
	void Move(Vector2<float> direction, sf::RenderWindow& window) {
		view.move(sf::Vector2f(direction.x, direction.y));
		window.setView(view);
	}

private:
	sf::View view;
};