#include "Core.hpp"

int main() {
  auto engine = std::make_shared<GobletOfFire::Core::CoreEngine>();

  engine->init();
  engine->run();
}