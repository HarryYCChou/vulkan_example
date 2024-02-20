#include "engine/de_window.h"

namespace de {

DeWindow::DeWindow(int w, int h, string name) : width{w}, height{h}, window_name{name} {
  InitWindow();
}

DeWindow::~DeWindow() {
  glfwDestroyWindow(window);
  glfwTerminate();
}

void DeWindow::InitWindow() {
  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

  window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
  //glfwSetWindowUserPointer(window, this);
  //glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

bool DeWindow::ShouldClose() {
  return glfwWindowShouldClose(window);
}

void DeWindow::CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
  if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
    throw runtime_error("failed to create window surface");
  }
}
}
