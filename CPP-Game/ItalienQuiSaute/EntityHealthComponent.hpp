#pragma once

#include "Component.hpp";

class EntityHealthComponent : public Component
{
public:
	EntityHealthComponent()
	{
		Health = 100.0f;
	}

	float GetHealth()
	{
		return Health;
	}

	float SetHealth(float newHealth)
	{
		Health = newHealth;
	}

	void TakeDamage(float amount)
	{
		Health -= amount;
	}

	void TakeHeal(float amount)
	{
		Health += amount;
	}
private:
	float Health;
};