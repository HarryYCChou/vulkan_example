#pragma once

#include "engine/de_device.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cassert>

using std::string;
using std::vector;
using std::ifstream;
using std::runtime_error;
using std::cout;
using std::endl;

namespace de {

struct PipelineConfigInfo {
  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  vector<VkDynamicState> dynamicStateEnables;
  VkPipelineDynamicStateCreateInfo dynamicStateInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  uint32_t subpass = 0;
};

class DePipeline {
 public:
  DePipeline(
      DeDevice& device,
      const string& vert_path,
      const string& frag_path,
      const PipelineConfigInfo& config_info);
  ~DePipeline();

  DePipeline(const DePipeline&) = delete;
  DePipeline& operator=(const DePipeline&) = delete;

  static void DefaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

  void bind(VkCommandBuffer commandBuffer);

 private:
  static vector<char> ReadFile(const string& file_path);
  void CreateGraphicsPipeline(
      const string& vert_path,
      const string& frag_path,
      const PipelineConfigInfo& config_info);
  void CreateShaderModule(
      const vector<char>& code,
      VkShaderModule* shader_module);

  DeDevice& de_device;
  VkPipeline graphics_pipeline;
  VkShaderModule vert_shader_module;
  VkShaderModule frag_shader_module;
};
}
