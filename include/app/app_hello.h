/*
 * Copyright (c) 2024 Harry Chou
 */

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>

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
using std::string;
using std::optional;
using std::set;
using std::numeric_limits;
using std::clamp;
using std::ios;
using std::ifstream;
using std::runtime_error;

// validation layer
const vector<const char*> validation_layers = {
  "VK_LAYER_KHRONOS_validation"
};
#ifdef NDEBUG
  const bool enable_validation_layers = false;
#else
  const bool enable_validation_layers = true;
#endif
// device extensions
const std::vector<const char*> device_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
// queue family indices
struct QueueFamilyIndices {
  optional<uint32_t> graphicsFamily;
  optional<uint32_t> presentFamily;

  bool isComplete() {
    return graphicsFamily.has_value();
  }
};
// swap chain
struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  vector<VkSurfaceFormatKHR> formats;
  vector<VkPresentModeKHR> presentModes;
};

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
  VkSurfaceKHR surface;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;
  VkQueue presentQueue;
  VkSwapchainKHR swapChain;
  vector<VkImage> swapChainImages;
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  vector<VkImageView> swapChainImageViews;
  VkRenderPass renderPass;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  // functions
  static vector<char> readFile(const string& filename) {
    ifstream file(filename, ios::ate | ios::binary);

    if (!file.is_open()) {
      throw runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t) file.tellg();
    vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
  }
  // vulkan function
  void init_window();
  void init_vulkan();
  void main_loop();
  void cleanup();
  void create_instance();
  // vulkan function - validation layers
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT&);
  bool check_validation_layer_support();
  void setupDebugMessenger();
  vector<const char*> get_required_extensions();
  static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  };
  // vulkan function - physical devices
  void pick_physical_device();
  bool is_device_suitable(VkPhysicalDevice);
  // vulkan function - queue family
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice);
  // vulkan function - logical device
  void create_logical_device();
  // vulkan function - surface
  void create_surface();
  // vulkan function - swapchain
  bool check_device_extension_support(VkPhysicalDevice);
  SwapChainSupportDetails query_swap_chain_support(VkPhysicalDevice);
  VkSurfaceFormatKHR choose_swap_surface_format(const vector<VkSurfaceFormatKHR>&);
  VkPresentModeKHR choose_swap_present_mode(const vector<VkPresentModeKHR>&);
  VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR&);
  void create_swap_chain();
  // vulkan function - image views 
  void create_image_views();
  // vulkan function - render pass
  void create_render_pass();
  // vulkan function - graphic pipeline
  void create_graphics_pipeline();
  VkShaderModule create_shader_module(const vector<char>&);
  // imgui function
  void setup_imgui();
};
