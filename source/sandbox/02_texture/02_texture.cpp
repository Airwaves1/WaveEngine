#include "wave_engine.hpp"

#include <glad/glad.h>

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
class Sandbox : public Application
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
        uint32_t vbo, ebo;

        // 生成vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // 生成vbo
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        // 将数据传入vbo
        glBufferData(GL_ARRAY_BUFFER, quad_vertices.size() * sizeof(float), quad_vertices.data(),
                     GL_STATIC_DRAW);

        // 生成ebo
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, quad_indices.size() * sizeof(uint32_t), quad_indices.data(), GL_STATIC_DRAW);

        // 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // 解绑vao
        glBindVertexArray(0);

        // 解绑vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 创建Shader
        std::string vertexShaderSource   = FileUtils::ReadFile(SHADER_DIR "00/02_texture.vert");
        std::string fragmentShaderSource = FileUtils::ReadFile(SHADER_DIR "00/02_texture.frag");

        m_shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource, false);

        // 加载纹理
        m_texture = std::make_shared<Texture>(TEXTURE_DIR "wood.png");

        // 设置纹理单元
        m_shader->bind();
        m_shader->setUniformInt("u_texture_0", 0);
    }

    void onRender() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 渲染
        m_shader->bind();
        m_texture->bind();
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, quad_indices.size(), GL_UNSIGNED_INT, 0);
    }

  private:
    uint32_t m_vao;
    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture> m_texture;
};

} // namespace Wave

Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }