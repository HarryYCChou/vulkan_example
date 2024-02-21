#pragma once

#include <string>
#include <stdexcept>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using std::string;
using std::runtime_error;

namespace de {

class DeWindow {
 public:
  DeWindow(int w, int h, string name);
  ~DeWindow();

  // avoid copy error
  DeWindow(const DeWindow&) = delete;
  DeWindow &operator=(const DeWindow&) = delete;

  bool ShouldClose();
  void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
 
 private:
  int width;
  int height;
  string window_name;
  GLFWwindow *window;

  void InitWindow();
};
}