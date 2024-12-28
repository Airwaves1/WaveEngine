#include "render/texture.hpp"
#include "utils/file_utils.hpp"
#include "wave_engine.hpp"


#include<glad/glad.h>

std::vector<float> quad_vertices = {
    // Position (x, y, z)     // UV (u, v)
    -0.5f, -0.5f,  0.0f,      0.0f, 0.0f,  // Bottom-left
     0.5f, -0.5f,  0.0f,      1.0f, 0.0f,  // Bottom-right
     0.5f,  0.5f,  0.0f,      1.0f, 1.0f,  // Top-right
    -0.5f,  0.5f,  0.0f,      0.0f, 1.0f   // Top-left
};

// Index data
std::vector<uint32_t> quad_indices = {
    0, 1, 2,  // First triangle
    0, 2, 3   // Second triangle
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

        uint32_t vbo;

        // 生成vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // 生成vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, quad_vertices.size() * sizeof(float), quad_vertices.data(),GL_STATIC_DRAW);

        // 生成veo
        glGenBuffers(1, &m_veo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_indices.size() * sizeof(uint32_t), quad_indices.data(), GL_STATIC_DRAW);
        // 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 解绑vao
        glBindVertexArray(0);

        // 创建shader
        std::string vertexShaderPath = std::string(SHADER_DIR) + "00/02_texture.vert";
        std::string fragShaderPath   = std::string(SHADER_DIR) + "00/02_texture.frag";
        // 读取源码文件
        std::string vertexShaderCode = FileUtils::ReadFile(vertexShaderPath);
        std::string fragShaderCode   = FileUtils::ReadFile(fragShaderPath);

        // 编译shader
        m_shader = std::make_shared<Shader>(vertexShaderCode, fragShaderCode, false);

        //加载纹理
        m_texture = std::make_shared<Texture>(std::string(TEXTURE_DIR) + "awesomeface.png");
        m_shader->bind();
        m_shader->setUniformInt("u_texture_0",0);
    }

    void onRender() override
    {
        // LOG_INFO("Sandbox Application is rendering!");
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        m_shader->bind();
        m_texture->bind();
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

  private:
    uint32_t m_vao;
    unsigned int m_veo;
    std::shared_ptr<Shader> m_shader{nullptr};
    std::shared_ptr<Texture> m_texture{nullptr};
};
} // namespace Wave
Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }