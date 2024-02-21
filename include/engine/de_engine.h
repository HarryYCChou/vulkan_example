#include "engine/de_window.h"
#include "engine/de_pipeline.h"
#include "engine/de_device.h"

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
  DePipeline de_pipeline{
      de_device,
      "../shaders/build/vert.spv",
      "../shaders/build/frag.spv",
      DePipeline::DefaultPipelineConfigInfo(WIDTH, HEIGHT)};
};
}
