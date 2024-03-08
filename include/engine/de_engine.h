#include "engine/de_window.h"
#include "engine/de_pipeline.h"
#include "engine/de_device.h"
#include "engine/de_swap_chain.h"
#include "engine/de_model.h"

#include <vector>
#include <memory>
#include <stdexcept>
#include <array>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::runtime_error;
using std::array;

namespace de {
class Engine{
 public:
  // parameters
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  // constructor
  Engine();
  ~Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  // function
  void run();

 private:
  void LoadModels();
  void CreatePipeline();
  void CreatePipelineLayout();
  void CreateCommandBuffers();
  void DrawFrame();
  void RecreateSwapChain();
  void RecordCommandBuffer(int image_index);

  DeWindow de_window{WIDTH, HEIGHT, "Engine"};
  DeDevice de_device{de_window};
  unique_ptr<DeSwapChain> de_swap_chain;
  unique_ptr<DePipeline> de_pipeline;
  VkPipelineLayout pipeline_layout;
  vector<VkCommandBuffer> command_buffers;
  unique_ptr<DeModel> de_model;
};
}
