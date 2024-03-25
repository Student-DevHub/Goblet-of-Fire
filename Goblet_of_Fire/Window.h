#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window {
public:
	Window(); // Default Window
	Window(const std::string& title, const sf::Vector2u& size); // Custom Window
	~Window();

	void BeginDraw(); //Clear Screen
	void EndDraw(); // Display

	void Update(); // Poll events (Close / Toggle Fullscreen)

	bool IsDone();
	bool IsFullscreen();
	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();

	void Draw(sf::Drawable& l_drawable);
private:
	void Setup(const std::string title, const sf::Vector2u& size); // Assign values to member variables
	void Create(); // Create Window using member variables
	void Destroy(); // Close Window

	// Keep track of window properties (for toggle fullscreen)
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
};