#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.hpp"
#include "Textures.hpp"
#include "SpriteRendererComponent.hpp"
#include "TransformComponent.hpp"
#include "InputManager.hpp"
#include "PlayerControllerComponent.hpp"
#include "HealthComponent.hpp"
#include "PlayerEntity.hpp"
#include "FileReader.hpp"

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

		Entity* entity = EM->CreateEntity("MY ENEMYYYY");
		Entity* entity2 = EM->CreateEntity("Momo");

		SpriteRendererComponent* spriteComp = new SpriteRendererComponent(tex);

		EM->CreateComponent("sprt", spriteComp);
		EM->AddComponent(entity, spriteComp);

		TransformComponent* transComp = new TransformComponent();

		EM->CreateComponent("trsf", transComp);
		EM->AddComponent(entity, transComp);

		SpriteRendererComponent* spriteComp2 = new SpriteRendererComponent(tex);

		EM->CreateComponent("sprt2", spriteComp2);
		EM->AddComponent(entity2, spriteComp2);
		// SpriteRendererComponent* compi = (SpriteRendererComponent*)EM.GetComponent(entity, 0);
		SpriteRendererComponent* compi = static_cast<SpriteRendererComponent*>(EM->GetComponent(entity, 1));
		SpriteRendererComponent* compi2 = static_cast<SpriteRendererComponent*>(EM->GetComponent(entity, 2));

		Entity* ent2 = EM->GetEntity(entity->UUID);

		ent2->Name = "OPOPO";

		sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

		sf::Event event{};
		InputManager inputManager(event);

		PlayerEntity* player = new PlayerEntity(EM);

		EM->destroyQueue.push_back(entity);

		sf::Time deltaTime = sf::Time(sf::microseconds(1.1f));
		sf::Time timeSinceStart = sf::Time(sf::microseconds(0));
		sf::Time timer = sf::Time(sf::microseconds(0));

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
			/*playerControllerComponent->Move(inputManager.GetDirection());

			std::cout << "current input : " << playerControllerComponent->GetDirectionX() << ";" << playerControllerComponent->GetDirectionY() << std::endl;
			*/
			if (timer.asMicroseconds() <= timeSinceStart.asMicroseconds()) {
				player->Move(inputManager.GetDirection(), sf::Time(sf::microseconds(2000)));
				timer += sf::Time(sf::microseconds(2000));
			}

			window.clear();

			for (Entity* ent : EM->livingEntityList)
			{
				for (Component* currentComponent : EM->componentMapping[ent])
				{
					if (currentComponent->Tag == "SPRITE_RENDERER") {
						SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
						window.draw(sprite->loadSprite());
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
