#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>

class Window {
public:
	Window(const std::string&);
	~Window();

	/* Event Updates */
	void update();

	/* Render Methods */
	void beginDraw();
	void draw(const sf::Drawable&);
	void endDraw();

	/* Helper Functions */
	bool isOpen() const;
	sf::Vector2u getCentre() const;

	sf::RenderWindow& getWindow() { return window; }

private:
	sf::RenderWindow window;

};

#endif /* Window_hpp */

/* To Add
- Toggle Fullscreen
- Read Configurations from file
*/
