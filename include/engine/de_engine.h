#include "engine/de_window.h"
#include "engine/de_pipeline.h"
#include "engine/de_device.h"
#include "engine/de_swap_chain.h"

#include <memory>

using std::unique_ptr;

namespace de {
class Engine{
 public:
  // parameters
  static constexpr int WIDTH = 800;
  static constexpr int HEIGHT = 600;

  // constructor
  Engine();
  ~Engine();

  // function
  void run();

 private:
  DeWindow de_window{WIDTH, HEIGHT, "Engine"};
  DeDevice de_device{de_window};
  DeSwapChain de_swap_chain{de_device, de_window.get_extent()};
  unique_ptr<DePipeline> de_pipeline;
  /*
  DePipeline de_pipeline{
      de_device,
      "../shaders/build/vert.spv",
      "../shaders/build/frag.spv",
      DePipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT)};
  */
};
}
