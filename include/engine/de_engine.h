#include "engine/de_window.h"
#include "engine/de_pipeline.h"
#include "engine/de_device.h"
#include "engine/de_swap_chain.h"

#include <vector>
#include <memory>
#include <stdexcept>

using std::vector;
using std::unique_ptr;
using std::runtime_error;

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
  void CreatePipeline();
  void CreatePipelineLayout();
  void CreateCommandBuffers();
  void DrawFrame();

  DeWindow de_window{WIDTH, HEIGHT, "Engine"};
  DeDevice de_device{de_window};
  DeSwapChain de_swap_chain{de_device, de_window.get_extent()};
  unique_ptr<DePipeline> de_pipeline;
  VkPipelineLayout pipeline_layout;
  vector<VkCommandBuffer> command_buffers;
};
}
