#include <iostream>
#include "T_CoreEngine.h"

int main() {
  auto engine = std::make_shared<GobletOfFire::Core::CoreEngine>();
  std::cerr << "Engine created..." << std::endl;

  engine->init();
  std::cerr << "Engine initialized..." << std::endl;

  engine->run();
  std::cerr << "Engine shutting down..." << std::endl;
  return 0;
}