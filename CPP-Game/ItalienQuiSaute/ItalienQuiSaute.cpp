// ItalienQuiSaute.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <SFML/Graphics.hpp>
#include <iostream>

#include "EntityManager.hpp"
#include "Textures.hpp"
#include "SpriteRendererComponent.hpp"

int main()
{
    EntityManager EM;
    Textures TEX;
    sf::Texture tex = TEX.loadTexture("Assets/Sprites/BlueContainer.png");
    sf::Texture tex2 = TEX.loadTexture("Assets/Sprites/rat.png");


    Entity* entity = EM.CreateEntity("MY ENEMYYYY");

    SpriteRendererComponent* spriteComp= new SpriteRendererComponent(tex);

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
  

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(compi->loadSprite());
        window.draw(compi2->loadSprite());


        window.display();
    }

    return 0;


    


}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
