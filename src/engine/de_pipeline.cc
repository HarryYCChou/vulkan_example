#include "engine/de_pipeline.h"

namespace de {
DePipeline::DePipeline(const string& vert_path, const string& frag_path) {
  CreateGraphicsPipeline(vert_path, frag_path);
}

DePipeline::~DePipeline() {}

vector<char> DePipeline::ReadFile(const string& file_path) {
  ifstream file{file_path, std::ios::ate | std::ios::binary};

  if (!file.is_open()) {
    throw runtime_error("failed to open file: " + file_path);
  }

  size_t file_size = static_cast<size_t>(file.tellg());
  vector<char> buffer(file_size);

  file.seekg(0);
  file.read(buffer.data(), file_size);

  file.close();
  return buffer;
}

void DePipeline::CreateGraphicsPipeline(const string& vert_path,
                                        const string& frag_path) {
  auto vert_code = ReadFile(vert_path);
  auto frag_code = ReadFile(frag_path);

  cout << "Vertex code size : " << vert_code.size() << endl;
  cout << "Fragment code size : " << vert_code.size() << endl;
}
}
