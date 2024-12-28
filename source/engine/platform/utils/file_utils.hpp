#pragma once

#include<string>

#ifdef PROJECT_ROOT_DIR
#define SHADER_DIR PROJECT_ROOT_DIR "/install/shaders/"
#define TEXTURE_DIR PROJECT_ROOT_DIR "/install/assets/textures/"
#define MODEL_DIR PROJECT_ROOT_DIR "/install/assets/models/"
#endif

namespace Wave
{
    class FileUtils
    {
        //读取文件内容
        public:
        static std::string ReadFile(const std::string& path);
        //获取文件大小
        static size_t GetFileSize(const std::string& path);

        private:
        FileUtils() = delete;
    };
}