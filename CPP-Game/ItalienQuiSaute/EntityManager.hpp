#pragma once
#include <iostream>

#include <vector>
#include <map>
#include "Entity.hpp"
#include "Component.hpp"

class EntityManager
{
public:

	std::vector<Entity*> livingEntityList;
	std::vector<Entity*> destroyQueue;

	std::vector<Component*> livingComponentList;
	std::map<Entity*, std::vector<Component*>> componentMapping;

#pragma region Entity

	void CreateEntity(std::string Name, Entity* entity)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		entity->Name = Name;
		entity->UUID = UUID;
		livingEntityList.push_back(entity);
	}
	Entity* CreateEntity(std::string Name)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		Entity* currentEntity = new Entity(UUID, Name, "");
		livingEntityList.push_back(currentEntity);
		return currentEntity;
	}
	Entity* CreateEntity(std::string Name, std::string Tag)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		Entity* currentEntity = new Entity(UUID, Name, Tag);
		livingEntityList.push_back(currentEntity);
		return currentEntity;
	}
	Entity* GetEntity(std::uint32_t UUID)
	{
		for (Entity* currentEntity : livingEntityList)
		{
			if (currentEntity->UUID == UUID)
			{
				return currentEntity;
			}
		}
	}
	

	void DestroyEntity(std::uint32_t UUID)
	{
		std::uint32_t index = 0;
		std::uint32_t itemToRemove = 0;
		for (Entity* currentEntity : livingEntityList)
		{
			index++;
			if (currentEntity->UUID == UUID)
			{
				itemToRemove = index;
				delete currentEntity;
			}
		}
		livingEntityList.erase(livingEntityList.begin() + itemToRemove);
	}

	void Purge()
	{

		int queue_size = destroyQueue.size()-1;
		if (queue_size >= 0) {
			for (int x = (queue_size); x >= 0; x--) {
				std::cout << x ;
				Entity* entity = destroyQueue.at(x);

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
#pragma endregion

#pragma region Component
	Component* CreateComponent()
	{
		std::uint32_t UUID = livingComponentList.size() + 1;
		Component* currentComponent = new Component(UUID, "");
		livingComponentList.push_back(currentComponent);
		return currentComponent;
	}



	Component* CreateComponent(std::string Name)
	{
		std::uint32_t UUID = livingComponentList.size() + 1;
		Component* currentComponent = new Component(UUID, Name);
		livingComponentList.push_back(currentComponent);
		return currentComponent;
	}

	void CreateComponent(std::string Name, Component* currentComponent)
	{
		const std::uint32_t UUID = livingComponentList.size() + 1;
		livingComponentList.push_back(currentComponent);

		currentComponent->UUID = UUID;
		currentComponent->Name = Name;
	}

	Component* GetComponent(Entity* entity, std::uint32_t componentUUID)
	{
		auto components = componentMapping.at(entity);

		for (Component* currentComponent : components)
		{
			if (currentComponent->UUID == componentUUID)
			{
				return currentComponent;
			}
		}
		return NULL;
	}

	Component* GetComponentByTag(Entity* entity, std::string Tag)
	{
		auto components = componentMapping.at(entity);

		for (Component* currentComponent : components)
		{
			if (currentComponent->Tag == Tag)
			{
				return currentComponent;
			}
		}
		return NULL;
	}

	void DestroyComponent(std::uint32_t UUID)
	{
		std::uint32_t index = 0;
		std::uint32_t itemToRemove = 0;
		for (Component* currentComponent : livingComponentList)
		{
			index++;
			if (currentComponent->UUID == UUID)
			{
				itemToRemove = index;
				delete currentComponent;
			}
		}
		livingComponentList.erase(livingComponentList.begin() + itemToRemove);
	}
	void AddComponent(Entity* entity, Component* component)
	{
		componentMapping[entity].push_back(component);
	}

	void RemoveComponent(Entity* entity, Component* component)
	{
		std::uint32_t index = 0;
		std::uint32_t componentToRemove = 0;
		for (Component* currentComponent : componentMapping[entity])
		{
			index++;
			if (currentComponent->UUID == component->UUID)
			{
				componentToRemove = index;
			}
			componentMapping[entity].erase(livingComponentList.begin() + componentToRemove);
		}
	}
#pragma endregion

private:
	int GetLivingEntityIndex(Entity* entity) {
		for (size_t i = 0; i < livingEntityList.size(); i++)
		{
			if (livingEntityList.at(i) == entity) {
				return i;
			}
		}
	}

	int GetLivingComponentIndex(Component* component) {
		for (size_t i = 0; i < livingComponentList.size(); i++)
		{
			if (livingComponentList.at(i) == component) {
				return i;
			}
		}
	}
};