#include <string>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

using std::string;

namespace de {

class DeWindow {
 public:
  DeWindow(int w, int h, string name);
  ~DeWindow();

  // avoid copy error
  DeWindow(const DeWindow&) = delete;
  DeWindow &operator=(const DeWindow&) = delete;

  bool ShouldClose();
 
 private:
  int width;
  int height;
  string window_name;
  GLFWwindow *window;

  void InitWindow();
};
}
