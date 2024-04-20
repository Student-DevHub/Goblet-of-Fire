#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window", sf::Style::Default);
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else if (event.type == sf::Event::Resized) {
        // Check if the window was maximized
        if (event.size.width == sf::VideoMode::getDesktopMode().width &&
          event.size.height == sf::VideoMode::getDesktopMode().height) {
          // Toggle fullscreen mode
          window.setFullscreen(!window.isFullscreen());
        }
      }
    }

    window.clear(sf::Color::White);
    // Draw your content here
    window.display();
  }

  return 0;
}
