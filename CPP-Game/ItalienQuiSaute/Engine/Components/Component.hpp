#pragma once

#include <string>

class Component
{
public:
	std::uint32_t UUID; //Is unique
	std::string Name;
	std::string Tag;

	Component() = default;

	Component(std::uint32_t UUID, std::string Name)
	{
		this->UUID = UUID;
		this->Name = Name;
		Tag = "DEFAULT";
	}
};
