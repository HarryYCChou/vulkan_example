#pragma once

#include "engine/de_device.h"

#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

using std::vector;

namespace de {

class DeModel {
 public:
  struct Vertex {
    glm::vec2 position;
    glm::vec3 color;

    static vector<VkVertexInputBindingDescription> GetBindingDescriptions();
    static vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();
  };

  DeModel(DeDevice& device, const vector<Vertex>& vertices);
  ~DeModel();
  DeModel(const DeModel&) = delete;
  DeModel& operator=(const DeModel&) = delete;

  void bind(VkCommandBuffer);
  void draw(VkCommandBuffer);

 private:
  DeDevice& de_device;
  VkBuffer vertex_buffer;
  VkDeviceMemory vertex_buffer_memory;
  uint32_t vertex_count;

  void CreateVertexBuffers(const vector<Vertex>& vertices);
};

}
