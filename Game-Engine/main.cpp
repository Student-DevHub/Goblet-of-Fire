#include "CoreEngine.hpp"
#include "InputManager.hpp"

int main() {
  auto engine = std::make_shared<GobletOfFire::Core::CoreEngine>();

  engine->init();
  engine->run();
}