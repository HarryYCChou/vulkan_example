#include "engine/de_engine.h"

namespace de {
Engine::Engine() {
  CreatePipelineLayout();
  CreatePipeline();
  CreateCommandBuffers();
}

Engine::~Engine() {
  vkDestroyPipelineLayout(de_device.device(), pipeline_layout, nullptr);
}

void Engine::run() {
  while (!de_window.ShouldClose()) {
    glfwPollEvents();
  }
}

void Engine::CreatePipeline() {
  auto pipelineConfig =
      DePipeline::DefaultPipelineConfigInfo(de_swap_chain.width(), de_swap_chain.height());
  pipelineConfig.renderPass = de_swap_chain.getRenderPass();
  pipelineConfig.pipelineLayout = pipeline_layout;
  de_pipeline = std::make_unique<DePipeline>(
      de_device,
      "../shaders/build/vert.spv",
      "../shaders/build/frag.spv",
      pipelineConfig);
}

void Engine::CreatePipelineLayout() {
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0;
  pipelineLayoutInfo.pSetLayouts = nullptr;
  pipelineLayoutInfo.pushConstantRangeCount = 0;
  pipelineLayoutInfo.pPushConstantRanges = nullptr;
  if (vkCreatePipelineLayout(de_device.device(), &pipelineLayoutInfo, nullptr, &pipeline_layout) !=
      VK_SUCCESS) {
    throw runtime_error("failed to create pipeline layout!");
  }
}

void Engine::CreateCommandBuffers() {

}

void Engine::DrawFrame() {

}

}
