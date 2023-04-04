#include <SFML/Graphics.hpp>
#include <iostream>

#include "SpriteRendererComponent.hpp"
#include "EntityManager.hpp"
#include "InputManager.hpp"
#include "Textures.hpp"
#include "playerControllerComponent.hpp"

int main()
{
	EntityManager EM;
	Textures TEX;
	sf::Texture tex = TEX.loadTexture("Assets/Sprites/BlueContainer.png");
	sf::Texture tex2 = TEX.loadTexture("Assets/Sprites/rat.png");

	Entity* entity = EM.CreateEntity("MY ENEMYYYY");

	SpriteRendererComponent* spriteComp = new SpriteRendererComponent(tex);

	EM.CreateComponent("sprt", spriteComp);
	EM.AddComponent(entity, spriteComp);

	SpriteRendererComponent* spriteComp2 = new SpriteRendererComponent(tex2);

	EM.CreateComponent("sprt2", spriteComp2);
	EM.AddComponent(entity, spriteComp2);
	// SpriteRendererComponent* compi = (SpriteRendererComponent*)EM.GetComponent(entity, 0);
	SpriteRendererComponent* compi = static_cast<SpriteRendererComponent*>(EM.GetComponent(entity, 1));
	SpriteRendererComponent* compi2 = static_cast<SpriteRendererComponent*>(EM.GetComponent(entity, 2));

	Entity* ent2 = EM.GetEntity(entity->UUID);

	ent2->Name = "OPOPO";

	std::cout << "Hello World!\n";
	std::cout << entity->Name << "\n";
	std::cout << ent2->Name << "\n";
	std::cout << spriteComp->Name << "\n";
	std::cout << compi->Name << "\n";

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	sf::Event event{};
	InputManager inputManager(event);
	PlayerControllerComponent playerController;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		inputManager.UpdateEvent(event);
		playerController.Move(inputManager.GetDirection());

		window.clear();
		window.draw(compi->loadSprite());
		window.draw(compi2->loadSprite());

		window.display();
	}
	return 0;
}
