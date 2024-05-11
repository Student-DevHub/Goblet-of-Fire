#include "Window.h"

Window::Window(const std::string& title)
	: window(sf::VideoMode(1280, 720), title, sf::Style::Titlebar) {
	window.setVerticalSyncEnabled(true);
}

Window::~Window() {}

void Window::update() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
		}
	}
}

void Window::beginDraw() {
	window.clear(sf::Color::White);
}

void Window::draw(const sf::Drawable& drawable) {
	window.draw(drawable);
}

void Window::endDraw() {
	window.display();
}

bool Window::isOpen() const {
	return window.isOpen();
}

sf::Vector2u Window::getCentre() const
{
	return sf::Vector2u(window.getSize().x/2, window.getSize().y / 2);
}
