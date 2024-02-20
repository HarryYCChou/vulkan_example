/*
 * Copyright (c) 2024 Harry Chou
 */

#include "vulkan_example/main.h"

int main() {
  // create an app
  //AppHello app;

  //try {
  //  app.run();
  //} catch (const exception& e) {
  //  cerr << e.what() << endl;
  //  return EXIT_FAILURE;
  //}

  // create engine
  de::Engine engine{};

  try {
    engine.run();
  } catch (const exception& e) {
    cerr << e.what() << endl;
    return EXIT_FAILURE;
  }

  return 0;
}

