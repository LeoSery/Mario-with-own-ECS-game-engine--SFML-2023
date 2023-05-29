#pragma once

#include "../../Engine/System/Libraries/Maths/Vector2.h";
#include "../../Engine/Entities/Background.hpp";
#include "Component.hpp";

#include <SFML/Graphics.hpp>;

class CameraComponent : public Component
{
public:
	//Camera for an entity
	CameraComponent(sf::RenderWindow& window, Vector2<float> center, Vector2<int> mapDimensions)
	{
		//Init base View
		this->mapDimensions = mapDimensions;
		view.setCenter(sf::Vector2f(center.x, center.y));
		view.setSize(sf::Vector2f(400.f, 400.f));
		view.zoom(5.0f);
		window.setView(view);
	}

	//Moving the camera and the background
	void Move(sf::Vector2f playerpos, Vector2<float> direction, sf::RenderWindow& window, Background* bg)
	{
		//Check corners and stop the camera if out of bounds
		if (playerpos.x + (view.getSize().x - view.getSize().x / 2) >= mapDimensions.x)
			direction.x = 0.0f;

		if (playerpos.y - (view.getSize().y) >= mapDimensions.y)
			direction.y = 0.0f;

		if (view.getCenter().x + playerpos.x - (view.getSize().x) <= 0)
			direction.x = 0.0f;

		if (view.getCenter().y - playerpos.y - (view.getSize().y) <= 0)
			direction.y = 0.0f;

		view.move(sf::Vector2f(direction.x, direction.y));
		bg->Move({ direction.x, direction.y });
		window.setView(view);
	}

private:
	Vector2<int> mapDimensions;
	sf::View view;
};