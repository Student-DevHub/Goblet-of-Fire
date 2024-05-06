#include <Core.hpp>

int main() {
  auto game = GobletOfFire::Core::CoreEngine::getInstance();
  game->init();
  game->run();
  
  return 0;
}
