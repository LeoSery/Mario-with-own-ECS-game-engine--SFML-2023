#pragma once

#include "../../Components/Component.hpp"
#include "../../Entities/Entity.hpp"

#include <iostream>
#include <vector>
#include <map>

class EntityManager
{
public:

	std::map<Entity*, std::vector<Component*>> componentMapping;
	std::vector<Component*> livingComponentList;
	std::vector<Entity*> livingEntityList;
	std::vector<Entity*> destroyQueue;

#pragma region Entity

	void CreateEntity(std::string Name, Entity* entity)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		entity->Name = Name;
		entity->UUID = UUID;
		livingEntityList.push_back(entity);
	}

	Entity* GetEntity(std::uint32_t UUID)
	{
		for (Entity* currentEntity : livingEntityList)
		{
			if (currentEntity->UUID == UUID)
				return currentEntity;
		}
	}

	//Get all entities of a category
	std::vector<Entity*> GetAllEntityByTag(std::string Tag)
	{
		std::vector<Entity*> allEntities;
		for (Entity* currentEntity : livingEntityList)
		{
			if (currentEntity->Tag == Tag)
				allEntities.push_back(currentEntity);
		}
		return allEntities;
	}

	//Destroy any entities in the destroy queue
	void Purge()
	{
		int queue_size = destroyQueue.size() - 1;
		if (queue_size >= 0)
		{
			//reverse loop entities
			for (int x = (queue_size); x >= 0; x--)
			{
				std::cout << x;
				Entity* entity = destroyQueue.at(x);

				//reverse loop components
				for (int i = componentMapping[entity].size() - 1; i >= 0; i--)
				{
					Component* component = componentMapping[entity].at(i);
					std::cout << "deleting Component: " << component->Name << "\n";
					auto iterator = componentMapping[entity].begin() + i;
					componentMapping[entity].erase(iterator);

					iterator = livingComponentList.begin() + GetLivingComponentIndex(component);
					livingComponentList.erase(iterator);

					delete component;
					std::cout << "deleted component" << "\n";
				}

				std::cout << "deleting entity: " << entity->Name << "\n";
				auto iterator = livingEntityList.begin() + GetLivingEntityIndex(entity);
				livingEntityList.erase(iterator);
				componentMapping.erase(destroyQueue.at(x));

				iterator = destroyQueue.begin() + x;
				destroyQueue.erase(iterator);

				delete entity;
				std::cout << "deleted entity" << "\n";
			}
		}
	}

	//Destroy all entities and components
	void PurgeAll()
	{
		for (Entity* ent : livingEntityList)
		{
			destroyQueue.push_back(ent);
		}
		Purge();
	}
#pragma endregion

#pragma region Component

	void CreateComponent(std::string Name, Component* currentComponent)
	{
		const std::uint32_t UUID = livingComponentList.size() + 1;
		livingComponentList.push_back(currentComponent);

		currentComponent->UUID = UUID;
		currentComponent->Name = Name;
	}

	void AddComponent(Entity* entity, Component* component)
	{
		componentMapping[entity].push_back(component);
	}

	Component* GetComponent(Entity* entity, std::uint32_t componentUUID)
	{
		auto components = componentMapping.at(entity);

		for (Component* currentComponent : components)
		{
			if (currentComponent->UUID == componentUUID)
				return currentComponent;
		}
		return NULL;
	}

	Component* GetComponentByTag(Entity* entity, std::string Tag)
	{
		auto components = componentMapping.at(entity);

		for (Component* currentComponent : components)
		{
			if (currentComponent->Tag == Tag)
				return currentComponent;
		}
		return NULL;
	}

#pragma endregion

private:
	int GetLivingEntityIndex(Entity* entity)
	{
		for (size_t i = 0; i < livingEntityList.size(); i++)
		{
			if (livingEntityList.at(i) == entity)
				return i;
		}
	}

	int GetLivingComponentIndex(Component* component)
	{
		for (size_t i = 0; i < livingComponentList.size(); i++)
		{
			if (livingComponentList.at(i) == component)
				return i;
		}
	}
};