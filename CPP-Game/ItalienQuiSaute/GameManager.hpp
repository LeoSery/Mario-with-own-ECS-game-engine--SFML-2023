#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.hpp"
#include "Textures.hpp"
#include "SpriteRendererComponent.hpp"
#include "Transform.hpp"

class GameManager
{
public:

    EntityManager EM;
    Textures TEX;
    sf::Texture tex = TEX.loadTexture("Assets/Sprites/BlueContainer.png");
    sf::Texture tex2 = TEX.loadTexture("Assets/Sprites/rat.png");

	GameManager() {

        Init();

	};


    void Init() {
        Update();
    }

	void Update() {

        


        Entity* entity = EM.CreateEntity("MY ENEMYYYY");

        SpriteRendererComponent* spriteComp = new SpriteRendererComponent(tex);

        EM.CreateComponent("sprt", spriteComp);
        EM.AddComponent(entity, spriteComp);


        TransformComponent* transComp = new TransformComponent();

        EM.CreateComponent("trsf", transComp);
        EM.AddComponent(entity, transComp);


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


        sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            for (Entity* ent : EM.livingEntityList) 
            {
                for (Component* currentComponent : EM.componentMapping[ent])
                {
                    SpriteRendererComponent* sprite = static_cast<SpriteRendererComponent*>(currentComponent);
                    window.draw(sprite->loadSprite());
                }
            }


            window.display();
        }
	}


};
