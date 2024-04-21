#include "Core.hpp"

int main() {
  auto engine = GobletOfFire::Core::CoreEngine::getInstance();

  engine->init();
  engine->run();
}