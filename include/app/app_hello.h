/*
 * Copyright (c) 2024 Harry Chou
 */

#include <iostream>
#include <vector>

// external libraries
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_vulkan.h"

using std::cout;
using std::endl;
using std::cerr;
using std::vector;

// validation layer
const vector<const char*> validation_layers = {
  "VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
  const bool enable_validation_layers = false;
#else
  const bool enable_validation_layers = true;
#endif

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
  VkDebugUtilsMessengerEXT debugMessenger;
  

  // functions
  // vulkan function
  void init_window();
  void init_vulkan();
  void main_loop();
  void cleanup();
  void create_instance();
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
  bool check_validation_layer_support();
  void setupDebugMessenger();
  vector<const char*> get_required_extensions();
  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  };
  // imgui function
  void setup_imgui();
};
