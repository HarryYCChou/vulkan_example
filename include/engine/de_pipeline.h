#pragma once

#include "engine/de_device.h"

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::runtime_error;
using std::cout;
using std::endl;

namespace de {

struct PipelineConfigInfo {};

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

  static PipelineConfigInfo DefaultPipelineConfigInfo(
      uint32_t width,
      uint32_t height);

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
