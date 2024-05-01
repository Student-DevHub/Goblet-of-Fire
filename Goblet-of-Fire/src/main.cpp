#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"

int main() {
  // Window creation
  sf::RenderWindow window(sf::VideoMode(800, 600), "Resource Manager Test");

  // Get the ResourceManager instance (Singleton)
  auto textureManager = GobletOfFire::Core::ResourceManager<sf::Texture>::getInstance();

  // Load textures
  textureManager->load(1);  // Load texture with ID 1 (assuming it exists)
  auto texture1 = textureManager->get(1);

  // Check if texture loaded successfully
  if (!texture1) {
    std::cerr << "Error: Could not get texture with ID 1!" << std::endl;
    return 1;
  }

  // Create a sprite for the loaded texture
  sf::Sprite sprite;
  sprite.setTexture(*texture1);

  // Main loop for window rendering
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // Clear window and draw sprite
    window.clear();
    window.draw(sprite);
    window.display();
  }

  return 0;
}
