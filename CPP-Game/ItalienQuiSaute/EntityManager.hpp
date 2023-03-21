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

	void DestoyEntity(std::uint32_t UUID)
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
		livingEntityList.erase(itemToRemove);
	}
	void DestoyEntity()
	{

	}
	void DestoyEntity()
	{

	}
private:
	std::vector<Entity> livingEntityList;
	std::vector<Component> livingComponentList;
	std::map<Entity, std::vector<Component>> componentMapping;
};