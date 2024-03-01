#include "engine/de_engine.h"

namespace de {
Engine::Engine() {
  LoadModels();
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
    DrawFrame();
  }

  vkDeviceWaitIdle(de_device.device());
}

void Engine::LoadModels() {
  vector<DeModel::Vertex> vertices = {
    {{0.0f, -0.5f}},
    {{0.5f, 0.5f}},
    {{-0.5f, 0.5f}}
  };
  de_model = make_unique<DeModel>(de_device, vertices);
}

void Engine::CreatePipeline() {
  auto pipelineConfig =
      DePipeline::DefaultPipelineConfigInfo(de_swap_chain.width(), de_swap_chain.height());
  pipelineConfig.renderPass = de_swap_chain.getRenderPass();
  pipelineConfig.pipelineLayout = pipeline_layout;
  de_pipeline = std::make_unique<DePipeline>(
      de_device,
      "../shaders/build/vert_2.spv",
      "../shaders/build/frag_2.spv",
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
  command_buffers.resize(de_swap_chain.imageCount());

  VkCommandBufferAllocateInfo allocInfo{};

  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = de_device.getCommandPool();
  allocInfo.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

  if (vkAllocateCommandBuffers(de_device.device(), &allocInfo, command_buffers.data()) !=
      VK_SUCCESS) {
    throw runtime_error("failed to allocate command buffers!");
  }

  for (int i = 0; i < command_buffers.size(); i++) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(command_buffers[i], &beginInfo) != VK_SUCCESS) {
      throw runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = de_swap_chain.getRenderPass();
    renderPassInfo.framebuffer = de_swap_chain.getFrameBuffer(i);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = de_swap_chain.getSwapChainExtent();

    array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(command_buffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    de_pipeline->bind(command_buffers[i]);
    de_model->bind(command_buffers[i]);
    de_model->draw(command_buffers[i]);

    vkCmdEndRenderPass(command_buffers[i]);
    if (vkEndCommandBuffer(command_buffers[i]) != VK_SUCCESS) {
      throw runtime_error("failed to record command buffer!");
    }
  } 
}

void Engine::DrawFrame() {
  uint32_t imageIndex;
  auto result = de_swap_chain.acquireNextImage(&imageIndex);
  if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
    throw runtime_error("failed to acquire swap chain image!");
  }

  result = de_swap_chain.submitCommandBuffers(&command_buffers[imageIndex], &imageIndex);
  if (result != VK_SUCCESS) {
    throw runtime_error("failed to present swap chain image!");
  }
}

}
