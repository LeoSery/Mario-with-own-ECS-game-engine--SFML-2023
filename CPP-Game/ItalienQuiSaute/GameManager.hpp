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
    sf::Texture tex = Textures::getTexture(0);
    sf::Texture tex2 = Textures::getTexture(1);

	GameManager() {

        Init();

	};


    void Init() {
        Update();
    }

	void Update() {

        


        Entity* entity = EM.CreateEntity("MY ENEMYYYY");
        Entity* entity2 = EM.CreateEntity("Momo");

        SpriteRendererComponent* spriteComp = new SpriteRendererComponent(tex);

        EM.CreateComponent("sprt", spriteComp);
        EM.AddComponent(entity, spriteComp);


        TransformComponent* transComp = new TransformComponent();

        EM.CreateComponent("trsf", transComp);
        EM.AddComponent(entity, transComp);


        SpriteRendererComponent* spriteComp2 = new SpriteRendererComponent(tex2);

        EM.CreateComponent("sprt2", spriteComp2);
        EM.AddComponent(entity2, spriteComp2);
        // SpriteRendererComponent* compi = (SpriteRendererComponent*)EM.GetComponent(entity, 0);
        SpriteRendererComponent* compi = static_cast<SpriteRendererComponent*>(EM.GetComponent(entity, 1));
        SpriteRendererComponent* compi2 = static_cast<SpriteRendererComponent*>(EM.GetComponent(entity, 2));



        Entity* ent2 = EM.GetEntity(entity->UUID);

        ent2->Name = "OPOPO";


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
