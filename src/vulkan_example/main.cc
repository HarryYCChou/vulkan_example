/*
 * Copyright (c) 2024 Harry Chou
 */

#include "vulkan_example/main.h"

int main() {
  // glfw initialization
  glfwInit();

  // create window 
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window",
                                        nullptr, nullptr);

  // check vulkan extension
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

  cout << extensionCount << " extensions supported" << endl;

  // main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  // glfw terminate
  glfwTerminate();

  return 0;
}

