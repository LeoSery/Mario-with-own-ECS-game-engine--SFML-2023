#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.hpp"
#include "Textures.hpp"
#include "SpriteRendererComponent.hpp"
#include "ColliderComponent.hpp"
#include "InputManager.hpp"
#include "PlayerControllerComponent.hpp"
#include "HealthComponent.hpp"
#include "PlayerEntity.hpp"
#include "Enemy.hpp"
#include "FileReader.hpp"

#include "Maths/Vector2.h"

class GameManager
{
public:
	EntityManager* EM = new EntityManager();
	sf::Texture tex = Textures::getTexture(0);
	sf::Texture tex2 = Textures::getTexture(1);

	GameManager() {
		Init();
	};

	void Init() {
		Update();
	}

	void Update() {



		sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

		sf::Event event{};
		InputManager inputManager(event);
		PlayerEntity* player = new PlayerEntity(EM, window);

		Enemy* enemy = new Enemy(EM, { 200.0f, 200.0f });

		sf::Time deltaTime = sf::Time(sf::microseconds(1.1f));
		sf::Time timeSinceStart = sf::Time(sf::microseconds(0));
		sf::Time timer = sf::Time(sf::microseconds(0));

		std::map<char, sf::Texture> gameMap;
		ReadMap mapReader;

		mapReader.ReadFile("Map.txt", gameMap, EM);

		EM->Purge();
		while (window.isOpen())
		{


			sf::Clock clock;

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			inputManager.UpdateEvent(event);


			window.clear();

			std::vector<Entity*> allEnemies = EM->GetAllEntityByTag("ENEMY");

			for (Entity* ent : EM->livingEntityList)
			{

				for (Component* currentComponent : EM->componentMapping[ent])
				{
					if (currentComponent->Tag == "SPRITE_RENDERER") {
						SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
						window.draw(sprite->loadSprite());

						if (ent->Tag != "PLAYER") {
							player->colliderComponent->Collision(sprite->getSprite());
						}

						if (ent->Tag != "ENEMY") {
							for (Entity* enemy : allEnemies) {
								Enemy* enemyEntity = static_cast<Enemy*>(enemy);
								enemyEntity->colliderComponent->Collision(sprite->getSprite());
							}
						}
					}

					else if (currentComponent->Tag == "HEALTH") {
						HealthComponent* entityHealth = static_cast<HealthComponent*>(currentComponent);
						if (entityHealth->isDead == true)
						{
							EM->destroyQueue.push_back(ent);
						}
					}
				}
			}

			EM->Purge();

			if (timer.asMicroseconds() <= timeSinceStart.asMicroseconds()) {

				player->Move(inputManager.GetDirection(), sf::Time(sf::microseconds(2000)), window);
				enemy->Move(sf::Time(sf::microseconds(2000)));
				timer += sf::Time(sf::microseconds(2000));
			}



			window.display();
			deltaTime = clock.getElapsedTime();
			timeSinceStart += deltaTime;
		}

		//clean pointers
		for (Entity* ent : EM->livingEntityList)
		{
			EM->destroyQueue.push_back(ent);
		}
		EM->Purge();
		delete EM;
	}
};
