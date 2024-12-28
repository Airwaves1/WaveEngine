#include "file_utils.hpp"
#include <fstream>
#include "log.hpp"

namespace Wave
{
    std::string FileUtils::ReadFile(const std::string &path)
    {
        std::string result;
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            LOG_ERROR("Failed to open file: {}", path);
        }

        return result;
    }

    size_t FileUtils::GetFileSize(const std::string &path)
    {
        std::ifstream in(path, std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            size_t size = in.tellg();
            in.close();
            return size;
        }
        else
        {
            LOG_ERROR("Failed to open file: {}", path);
        }
        return 0;
    }
}
