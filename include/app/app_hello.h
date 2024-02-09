/*
 * Copyright (c) 2024 Harry Chou
 */

#include <iostream>

// external libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using std::cout;
using std::endl;

class AppHello {
 public:
  // constructor
  AppHello() {}
  ~AppHello() {}

  // parameters
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

  // functions
  void run();

 private:
  GLFWwindow* window;
  VkInstance instance;
  
  // functions
  void init_window();
  void init_vulkan();
  void main_loop();
  void cleanup();
  void create_instance();
};
