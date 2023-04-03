#pragma once
#include <iostream>

#include <vector>
#include <map>

#include "Entity.hpp"
#include "Component.hpp"

class EntityManager
{
public:
#pragma region Entity
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
#pragma endregion

#pragma region Component
	void CreateComponent()
	{
		std::uint32_t UUID = livingComponentList.size() + 1;
		Component currentComponent(UUID, "");
		livingComponentList.push_back(currentComponent);
	}

	Component GetComponent(const Entity& entity, std::uint32_t componentUUID)
	{
		const auto components = componentMapping.at(entity);
		for (Component currentComponent : components)
		{
			if (currentComponent.UUID == componentUUID)
			{
				return currentComponent;
			}
		}
	}

	void DestroyComponent(std::uint32_t UUID)
	{
		std::uint32_t index = 0;
		std::uint32_t itemToRemove = 0;
		for (Component& currentComponent : livingComponentList)
		{
			index++;
			if (currentComponent.UUID == UUID)
			{
				itemToRemove = index;
			}
		}
		livingComponentList.erase(livingComponentList.begin() + itemToRemove);
	}

	void AddComponent(Entity& entity, Component& component)
	{
		std::vector<Component> componentlist;

		for (auto& [key, value] : componentMapping)
		{
			if (key.UUID == entity.UUID) {
				componentMapping[entity] = componentlist;
			}
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
#pragma endregion

private:
	std::vector<Entity> livingEntityList;
	std::vector<Component> livingComponentList;
	std::map<Entity, std::vector<Component>> componentMapping;
};