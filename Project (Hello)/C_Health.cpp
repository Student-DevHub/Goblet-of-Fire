#include "C_Health.h"

C_Health::C_Health(Object *owner,int health=100):Component(owner){
	currentHealth = health;
}
void C_Health::activate() {}
void C_Health::create(int health){}
void C_Health::take_damage(int damage) {
	currentHealth -= damage;
}
void heal(int value){}