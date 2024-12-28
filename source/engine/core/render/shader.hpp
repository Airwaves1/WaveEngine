#pragma once

#include <glad/glad.h>
#include <string>
#include<glm/glm.hpp>
#include<unordered_map>

namespace Wave
{
class Shader
{
  public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath, bool fromFile = true);
    ~Shader();

    void bind() const;
    void unbind() const;
    // 编译错误检验
    uint32_t compile(const std::string &source, GLenum shaderType);
    uint32_t link(const uint32_t& vertexShader, const uint32_t& fragmentShader);

    uint32_t getUniformLocation(const std::string &name);
    void setUniformBool(const std::string &name, bool value);
    void setUniformInt(const std::string &name, int value);
    void setUniformFloat(const std::string &name, float value);
    void setUniformFloat2(const std::string &name, const glm::vec2 &value);
    void setUniformFloat3(const std::string &name, const glm::vec3 &value);
    void setUniformFloat4(const std::string &name, const glm::vec4 &value);
    void setUniformMat3(const std::string &name, const glm::mat3 &value);
    void setUniformMat4(const std::string &name, const glm::mat4 &value);

    uint32_t getHandle() const { return m_handle; }

  private:
    std::string m_vertexShaderSource;
    std::string m_fragmentShaderSource;

    uint32_t m_handle = 0;
    std::unordered_map<std::string,uint32_t> m_uniformLocationCache;
    std::unordered_map<std::string, uint32_t> m_uniformErrordCache;

};
} // namespace Wave