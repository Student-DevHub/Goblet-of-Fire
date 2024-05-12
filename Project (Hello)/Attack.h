#pragma once
#include "C_Transform.h"
#include "C_Health.h"
#include "Component.h"
#include "Object.h"
#include<cmath>


class Attack:public Component
{
public:
	Attack(Object *owner,int damage):Component(owner),damage(damage){}
	void attack(Object* reciever){
		auto player1X = owner->GetComponent<C_Transform>()->getPosition().x;
		auto player2X = reciever->GetComponent<C_Transform>()->getPosition().x;
		
		// If both players position are within 20px of each other then attack 
		if (std::abs(player1X - player2X) <= 20) {
			reciever->GetComponent<C_Health>()->take_damage(damage);
		}
	}


private:
	int damage;

};

