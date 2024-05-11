#include "Input.h"

bool Input::isKeyPressed(Key keycode) {
	return currentFrameKeys.getBit((int)keycode);
}

bool Input::isKeyDown(Key keycode) {
	bool lastFrame = previousFrameKeys.getBit((int)keycode);
	bool currentFrame = currentFrameKeys.getBit((int)keycode);

	/* If key pressed thisFrame but not in lastFrame */
	return currentFrame && !lastFrame;
}

bool Input::isKeyUp(Key keycode) {
	bool lastFrame = previousFrameKeys.getBit((int)keycode);
	bool currentFrame = currentFrameKeys.getBit((int)keycode);

	/* If key pressed lastFrame but not in currentFrame */
	return !currentFrame && lastFrame;
}

sf::Vector2i Input::getMouseBox(Window& window)
{
	return sf::Mouse::getPosition(window.getWindow());
}

void Input::update() {
	previousFrameKeys.setBitMask(currentFrameKeys);

	currentFrameKeys.setBit( 
		(int) Key::Left,
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
	);

	currentFrameKeys.setBit(
		(int) Key::Right,
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
	);

	currentFrameKeys.setBit(
		(int) Key::Up,
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
	);

	currentFrameKeys.setBit(
		(int) Key::Down,
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
	);

	currentFrameKeys.setBit(
		(int) Key::ESC,
		sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
	);

	currentFrameKeys.setBit(
		(int)Key::MouseLeft,
		sf::Mouse::isButtonPressed(sf::Mouse::Left)
	);
	currentFrameKeys.setBit(
		(int)Key::W, 
		sf::Keyboard::isKeyPressed(sf::Keyboard::W)
	);
	currentFrameKeys.setBit(
		(int)Key::A,
		sf::Keyboard::isKeyPressed(sf::Keyboard::A)
	);
	currentFrameKeys.setBit(
		(int)Key::S,
		sf::Keyboard::isKeyPressed(sf::Keyboard::S)
	);
	currentFrameKeys.setBit(
		(int)Key::D,
		sf::Keyboard::isKeyPressed(sf::Keyboard::D)
	);

	currentFrameKeys.setBit(
		(int)Key::X, sf::Keyboard::isKeyPressed(sf::Keyboard::X) //end of bit
	);
}
