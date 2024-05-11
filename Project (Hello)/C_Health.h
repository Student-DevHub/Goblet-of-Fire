#pragma once
#include "Component.h"
class C_Health:public Component
{
public:
	C_Health(Object * owner,int health);
	void activate();
	void create(int health);
	void take_damage(int damage);
	void heal(int value);


private:
	unsigned int currentHealth;
};

