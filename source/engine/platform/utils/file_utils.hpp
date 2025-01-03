#pragma once

#include <string>

#ifdef PROJECT_ROOT_DIR
#define SHADER_DIR PROJECT_ROOT_DIR "/install/shaders/"
#define TEXTURE_DIR PROJECT_ROOT_DIR "/install/assets/textures/"
#define MODEL_DIR PROJECT_ROOT_DIR "/install/assets/models/"
#endif

namespace Wave
{
class FileUtils
{
  public:
    // 读取文件的内容
    static std::string ReadFile(const std::string &filepath);

    // 获取文件大小
    static size_t GetFileSize(const std::string &filepath);

  private:
    FileUtils() = delete;
};

} // namespace Wave