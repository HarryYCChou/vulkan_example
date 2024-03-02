#include "engine/de_model.h"

#include <cassert>
#include <cstring>

namespace de {

DeModel::DeModel(DeDevice& device, const vector<Vertex>& vertices) : de_device{device} {
  CreateVertexBuffers(vertices);
}

DeModel::~DeModel() {
  vkDestroyBuffer(de_device.device(), vertex_buffer, nullptr);
  vkFreeMemory(de_device.device(), vertex_buffer_memory, nullptr);
}

void DeModel::draw(VkCommandBuffer commandBuffer) {
  vkCmdDraw(commandBuffer, vertex_count, 1, 0, 0);
}

void DeModel::bind(VkCommandBuffer commandBuffer) {
  VkBuffer buffers[] = {vertex_buffer};
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);
}

vector<VkVertexInputBindingDescription> DeModel::Vertex::GetBindingDescriptions() {
  vector<VkVertexInputBindingDescription> bindingDescriptions(1);
  bindingDescriptions[0].binding = 0;
  bindingDescriptions[0].stride = sizeof(Vertex);
  bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  return bindingDescriptions;
}

vector<VkVertexInputAttributeDescription> DeModel::Vertex::GetAttributeDescriptions() {
  vector<VkVertexInputAttributeDescription> attributeDescriptions(2);

  attributeDescriptions[0].binding = 0;
  attributeDescriptions[0].location = 0;
  attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
  attributeDescriptions[0].offset = offsetof(Vertex, position);

  attributeDescriptions[1].binding = 0;
  attributeDescriptions[1].location = 1;
  attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
  attributeDescriptions[1].offset = offsetof(Vertex, color);

  return attributeDescriptions;
}

void DeModel::CreateVertexBuffers(const vector<Vertex>& vertices) {
  vertex_count = static_cast<uint32_t>(vertices.size());
  assert(vertex_count >= 3 && "Vertex count must be at least 3");

  VkDeviceSize bufferSize = sizeof(vertices[0]) * vertex_count;

  de_device.createBuffer(
    bufferSize,
    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
    vertex_buffer,
    vertex_buffer_memory);

  void *data;
  vkMapMemory(de_device.device(), vertex_buffer_memory, 0, bufferSize, 0, &data);
  memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
  vkUnmapMemory(de_device.device(), vertex_buffer_memory);
}
}
