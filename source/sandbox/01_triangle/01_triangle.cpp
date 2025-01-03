#include "wave_engine.hpp"

// 测试一下文件读取，写个Shader

// 三角形数据
std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f, // left
    0.5f,  -0.5f, 0.0f, // right
    0.0f,  0.5f,  0.0f  // top
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
        // 生成vao
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // 生成vbo
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        // 将数据传入vbo
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(),
                     GL_STATIC_DRAW);

        // 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);

        // 解绑vao
        glBindVertexArray(0);

        // 解绑vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 创建Shader
        std::string vertexShaderSource   = FileUtils::ReadFile(SHADER_DIR "00/01_triangle.vert");
        std::string fragmentShaderSource = FileUtils::ReadFile(SHADER_DIR "00/01_triangle.frag");

        m_shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource, false);
    }

    void onRender() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // 渲染
        m_shader->bind();
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

  private:
    uint32_t m_vao, m_vbo;
    std::shared_ptr<Shader> m_shader;
};

} // namespace Wave

Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }