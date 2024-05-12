#pragma once

#include "BitMask.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class Input {
public:
	/* Bit Positions of Each Key */
	enum class Key
	{
		None = 0,
		Left = 1,
		Right = 2,
		Up = 3,
		Down = 4,
		ESC = 5,
		MouseLeft = 6,
		W = 7,
		A = 8,
		S = 9,
		D = 10,
		X = 11
	};

	bool isKeyPressed(Key keycode);
	bool isKeyDown(Key keycode); // True if key just pressed
	bool isKeyUp(Key keycode); // True if key just released

	sf::Vector2i getMouseBox(Window&);

	/* Set Respective Position as 1 in Mask if Key Pressed */
	void update();

private:
	/* Both Frames to determine if just Released/Pressed */
	BitMask currentFrameKeys;
	BitMask previousFrameKeys;
};

