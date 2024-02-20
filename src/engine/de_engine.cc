#include "engine/de_engine.h"

namespace de {
Engine::Engine() {}
Engine::~Engine() {}
void Engine::run() {
  while (!de_window.ShouldClose()) {
    glfwPollEvents();
  }
}
}
