#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Window.h"

int main(int argc, char* argv[]) {
	GobletOfFire::Window myWindow("Goblet of Fire");

	while (myWindow.isCreated()) {
		sf::Event event;
		if (myWindow.getPollEvent(event)) {
			if (event.type == sf::Event::Closed)
				break;
		}

		myWindow.beginDraw();
		myWindow.endDraw();
	}

	return EXIT_SUCCESS;
}