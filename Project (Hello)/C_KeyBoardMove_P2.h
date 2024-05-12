#pragma once

#include "Component.h"
#include "Input.h"

class C_KeyboardMove_P2 : public Component {
public:
	C_KeyboardMove_P2(Object* owner);

	void setInput(Input* input);
	void setMovementSpeed(int moveSpeed);

	void update(float dt) override;
	/*void attack(Object* reciever,float dt);*/

private:
	Input* input;
	int moveSpeed;
};

