#include "engine/de_pipeline.h"

namespace de {
DePipeline::DePipeline(
    DeDevice& device,
    const string& vert_path,
    const string& frag_path,
    const PipelineConfigInfo& config_info) : de_device{device} {
  CreateGraphicsPipeline(vert_path, frag_path, config_info);
}

DePipeline::~DePipeline() {}

vector<char> DePipeline::ReadFile(const string& file_path) {
  ifstream file{file_path, std::ios::ate | std::ios::binary};

  if (!file.is_open()) {
    throw runtime_error("failed to open file: " + file_path);
  }

  size_t file_size = static_cast<size_t>(file.tellg());
  vector<char> buffer(file_size);

  file.seekg(0);
  file.read(buffer.data(), file_size);

  file.close();
  return buffer;
}

void DePipeline::CreateGraphicsPipeline(
    const string& vert_path,
    const string& frag_path,
    const PipelineConfigInfo& config_info) {
  auto vert_code = ReadFile(vert_path);
  auto frag_code = ReadFile(frag_path);

  cout << "Vertex code size : " << vert_code.size() << endl;
  cout << "Fragment code size : " << vert_code.size() << endl;
}

void DePipeline::CreateShaderModule(
    const vector<char>& code,
    VkShaderModule* shader_module) {
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  if (vkCreateShaderModule(de_device.device(), &createInfo, nullptr, shader_module) != VK_SUCCESS) {
    throw std::runtime_error("failed to create shader module");
  }
}

PipelineConfigInfo DePipeline::DefaultPipelineConfigInfo(
    uint32_t width,
    uint32_t height) {
  PipelineConfigInfo config_info{};
  return config_info;
}
}
