#include "engine/de_window.h"
#include "engine/de_pipeline.h"

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
  DePipeline de_pipeline{"../shaders/build/vert.spv", "../shaders/build/frag.spv"};
};
}
