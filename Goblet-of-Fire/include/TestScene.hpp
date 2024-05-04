#pragma once

#include <chrono>

#include <SFML/Graphics.hpp>

#include <Scene.hpp>

namespace GobletOfFire {
  namespace Scene {
    class MyScene : public iScene {
    public:
      MyScene() : renderTexture(std::make_shared<sf::RenderTexture>()) {}

      void create() override {
        renderTexture->create(800, 600);
        shape.setSize(sf::Vector2f(100.f, 100.f));
        shape.setPosition(350.f, 250.f);
        shape.setFillColor(sf::Color::Red);
      }

      void destroy() override {
        renderTexture.reset();
      }

      void activate() override {
        lastColorChange = std::chrono::steady_clock::now();
      }

      void deactivate() override {
        // No cleanup needed for deactivation
      }

      void updateLogic() override {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - lastColorChange).count();

        // Change color every 10 seconds
        if (duration >= 10) {
          changeColor();
          lastColorChange = now;
        }
      }

      void updateRender() override {
        renderTexture->clear();
        renderTexture->draw(shape);
        renderTexture->display();
      }

      std::shared_ptr<sf::RenderTexture> getBuffer() const override {
        return renderTexture;
      }

    private:
      void changeColor() {
        static int colorIndex = 0;
        sf::Color colors[] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue };
        shape.setFillColor(colors[colorIndex]);
        colorIndex = (colorIndex + 1) % 3;
      }

      std::shared_ptr<sf::RenderTexture> renderTexture;
      sf::RectangleShape shape;
      std::chrono::time_point<std::chrono::steady_clock> lastColorChange;
    };
  }
}