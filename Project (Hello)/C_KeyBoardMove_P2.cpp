#include "C_KeyboardMove_P2.h"
#include "Object.h"
#include "Attack.h"
#include<iostream>

//This is the second keyboard class for Player 2
C_KeyboardMove_P2::C_KeyboardMove_P2(Object* owner) : Component(owner), moveSpeed(100), input(nullptr)
{
}

void C_KeyboardMove_P2::setInput(Input* input) {
    this->input = input;
}

void C_KeyboardMove_P2::setMovementSpeed(int moveSpeed) {
    this->moveSpeed = moveSpeed;
}

void C_KeyboardMove_P2::update(float dt) {
    if (input == nullptr)
        return;

    int xMove = 0;
    if (input->isKeyPressed(Input::Key::A))
    {
        xMove = -moveSpeed;
    }
    else if (input->isKeyPressed(Input::Key::D))
    {
        xMove = moveSpeed;
    }

    int yMove = 0;
    if (input->isKeyPressed(Input::Key::W))
    {
        yMove = -moveSpeed;
    }
    else if (input->isKeyPressed(Input::Key::S))
    {
        yMove = moveSpeed;
    }


    owner->transform->addPosition(xMove * dt, yMove * dt);
}

//
//void C_KeyboardMove_P2::attack(Object *reciever,float dt) {
//       if (input->isKeyPressed(Input::Key::X)) {
//           std::cout << "Attacking bro";
//           owner->GetComponent<Attack>()->attack(reciever);
//    }
//}