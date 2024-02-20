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
class DePipeline {
 public:
  DePipeline(const string& vert_path, const string& frag_path);
  ~DePipeline();

 private:
  static vector<char> ReadFile(const string& file_path);
  void CreateGraphicsPipeline(const string& vert_path, const string& frag_path); 
};
}
