#include "engine/de_window.h"

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
};
}
