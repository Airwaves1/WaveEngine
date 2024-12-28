#include <iostream>
#include "application/application.hpp"
#include "application/entry_point.hpp"

#include "utils/log.hpp"
#include "utils/file_utils.hpp"
#include <iostream>
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <render/shader.hpp>

std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, // bottom left
    0.5f,  -0.5f, 0.0f, // bottom right
    0.0f,  0.5f,  0.0f  // top
};

namespace Wave
{

class Sandbox : public Wave::Application
{
  public:
    Sandbox() {}
    ~Sandbox() {}

  protected:
    void onConfigurate(ApplicationConfig &config) override
    {
        config.width  = 1400;
        config.height = 800;
        config.title  = "Wave Engine Sandbox";
    }

    void onInit() override
    {
        LOG_INFO("Sandbox Application is running!");

        // 生成vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // 生成vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        // 填充数据
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     GL_STATIC_DRAW);
        // 设置 顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        // 解绑vbo vao
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // 创建shader
        std::string vertexShaderPath = std::string(SHADER_DIR) + "00/00_test.vert";
        std::string fragShaderPath   = std::string(SHADER_DIR) + "00/00_test.frag";
        // 读取源码文件
        std::string vertexShaderCode = FileUtils::ReadFile(vertexShaderPath);
        std::string fragShaderCode   = FileUtils::ReadFile(fragShaderPath);

        // 编译shader
        m_shader = std::make_shared<Shader>(vertexShaderCode, fragShaderCode, false);
    }

    void onRender() override
    {
        // LOG_INFO("Sandbox Application is rendering!");
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_shader->bind();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

  private:
    uint32_t m_vao, m_vbo;
    std::shared_ptr<Shader> m_shader{nullptr};
};
} // namespace Wave
Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }