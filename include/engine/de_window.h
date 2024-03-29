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
  VkExtent2D get_extent() {
      return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  };
  bool WasWindowResized() { return frame_buffer_resized; }
  void ResetWindowResizedFlag() { frame_buffer_resized = false; } 

  void CreateWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
 
 private:
  int width;
  int height;
  bool frame_buffer_resized = false;

  string window_name;
  GLFWwindow *window;

  void InitWindow();
  static void FrameBufferResizeCallback(GLFWwindow* window, int width, int height);
};
}
