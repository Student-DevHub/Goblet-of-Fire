#include "C_KeyboardMove_P1.h"
#include "Object.h"
#include "Attack.h"
#include<iostream>

C_KeyboardMove_P1::C_KeyboardMove_P1(Object* owner): Component(owner), moveSpeed(100), input(nullptr)
{
}

void C_KeyboardMove_P1::setInput(Input* input) {
	this->input = input;
}

void C_KeyboardMove_P1::setMovementSpeed(int moveSpeed) {
	this->moveSpeed = moveSpeed;
}

void C_KeyboardMove_P1::update(float dt) {
	if (input == nullptr)
		return;
	
	int xMove = 0;
    if (input->isKeyPressed(Input::Key::Left))
    {
        xMove = -moveSpeed;
    }
    else if (input->isKeyPressed(Input::Key::Right))
    {
        xMove = moveSpeed;
    }

    int yMove = 0;
    if (input->isKeyPressed(Input::Key::Up))
    {
        yMove = -moveSpeed;
    }
    else if (input->isKeyPressed(Input::Key::Down))
    {
        yMove = moveSpeed;
    }
    

    owner->transform->addPosition(xMove * dt, yMove * dt);
}

//
void C_KeyboardMove_P1::attack(Object *reciever,float dt) {
    if (input->isKeyPressed(Input::Key::X)) {
    std::cout << "Attacking bro";
    owner->GetComponent<Attack>()->attack(reciever);
        }
    }