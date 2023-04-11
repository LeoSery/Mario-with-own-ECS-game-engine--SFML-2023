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
		const std::uint32_t UUID = livingComponentList.size()+1;
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

	
};