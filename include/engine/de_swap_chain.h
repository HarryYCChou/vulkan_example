#pragma once

#include "de_device.h"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <string>
#include <vector>

using std::min;
using std::vector;
using std::string;

namespace de {

class DeSwapChain {
 public:
  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

  DeSwapChain(DeDevice &deviceRef, VkExtent2D windowExtent);
  ~DeSwapChain();

  DeSwapChain(const DeSwapChain &) = delete;
  DeSwapChain& operator=(const DeSwapChain &) = delete;

  VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
  VkRenderPass getRenderPass() { return renderPass; }
  VkImageView getImageView(int index) { return swapChainImageViews[index]; }
  size_t imageCount() { return swapChainImages.size(); }
  VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
  VkExtent2D getSwapChainExtent() { return swapChainExtent; }
  uint32_t width() { return swapChainExtent.width; }
  uint32_t height() { return swapChainExtent.height; }

  float extentAspectRatio() {
    return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
  }
  VkFormat findDepthFormat();

  VkResult acquireNextImage(uint32_t *imageIndex);
  VkResult submitCommandBuffers(const VkCommandBuffer *buffers, uint32_t *imageIndex);

 private:
  void createSwapChain();
  void createImageViews();
  void createDepthResources();
  void createRenderPass();
  void createFramebuffers();
  void createSyncObjects();

  // Helper functions
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;

  vector<VkFramebuffer> swapChainFramebuffers;
  VkRenderPass renderPass;

  vector<VkImage> depthImages;
  vector<VkDeviceMemory> depthImageMemorys;
  vector<VkImageView> depthImageViews;
  vector<VkImage> swapChainImages;
  vector<VkImageView> swapChainImageViews;

  DeDevice &device;
  VkExtent2D windowExtent;

  VkSwapchainKHR swapChain;

  vector<VkSemaphore> imageAvailableSemaphores;
  vector<VkSemaphore> renderFinishedSemaphores;
  vector<VkFence> inFlightFences;
  vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};

}
