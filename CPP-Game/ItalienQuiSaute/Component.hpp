#pragma once

#include <string>

class Component
{
public:
	std::uint32_t UUID;
	std::string Name;
	Component() = default;
	Component(std::uint32_t UUID, std::string Name)
	{
		this->UUID = UUID;
		this->Name = Name;
	}
};
