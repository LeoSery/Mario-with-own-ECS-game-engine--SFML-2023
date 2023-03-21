#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Component.hpp"
#include <vector>
#include <map>

class EntityManager
{
public:
	void CreateEntity()
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		Entity currentEntity(UUID, "", "");
		livingEntityList.push_back(currentEntity);
	}
	void CreateEntity(std::string Name)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		Entity currentEntity(UUID, Name, "");
		livingEntityList.push_back(currentEntity);
	}
	void CreateEntity(std::string Name, std::string Tag)
	{
		std::uint32_t UUID = livingEntityList.size() + 1;
		Entity currentEntity(UUID, Name, Tag);
		livingEntityList.push_back(currentEntity);
	}

	Entity GetEntity(std::uint32_t UUID)
	{
		for (Entity& currentEntity : livingEntityList)
		{
			if (currentEntity.UUID == UUID)
			{
				return currentEntity;
			}
		}
	}

	void DestroyEntity(std::uint32_t UUID)
	{
		std::uint32_t index = 0;
		std::uint32_t itemToRemove = 0;
		for (Entity& currentEntity : livingEntityList)
		{
			index++;
			if (currentEntity.UUID == UUID)
			{
				itemToRemove = index;
			}
		}
		livingEntityList.erase(livingEntityList.begin() + itemToRemove);
	}

	void AddComponent(Entity& entity, Component& component)
	{
		std::vector<Component> componentList;
		if (!componentMapping.contains(entity))
		{
			componentMapping[entity] = componentList;
		}
		componentMapping[entity].push_back(component);
	}

	void RemoveComponent(Entity& entity, Component& component)
	{
		std::uint32_t index = 0;
		std::uint32_t componentToRemove = 0;
		for (Component currentComponent : componentMapping[entity])
		{
			index++;
			if (currentComponent.UUID == component.UUID)
			{
				componentToRemove = index;
			}
			componentMapping[entity].erase(livingComponentList.begin() + componentToRemove);
		}
	}

	Component GetComponent(Entity& entity, std::uint32_t compoentUUID)
	{
		for (Component currentComponent : componentMapping[entity])
		{
			if (currentComponent.UUID == compoentUUID)
			{
				return currentComponent;
			}
		}
	}

private:
	std::vector<Entity> livingEntityList;
	std::vector<Component> livingComponentList;
	std::map<Entity, std::vector<Component>> componentMapping;
};