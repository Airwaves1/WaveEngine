#include "wave_engine.hpp"

#include <glad/glad.h>

#include <vector>

// 顶点数据：位置 (x, y, z)，UV (u, v)，法线 (nx, ny, nz)
std::vector<float> cube_vertices = {
    // Front face
    -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-left
    1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom-right
    1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Top-right
    -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Top-left

    // Back face
    -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Bottom-right
    1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Bottom-left
    1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,   // Top-left
    -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  // Top-right

    // Left face
    -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
    -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Bottom-right
    -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,   // Top-right
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  // Top-left

    // Right face
    1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom-right
    1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Bottom-left
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Top-left
    1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Top-right

    // Top face
    -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-left
    1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Top-right
    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Bottom-right
    -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom-left

    // Bottom face
    -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Top-right
    1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // Top-left
    1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,   // Bottom-left
    -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f   // Bottom-right
};

// 索引数据
std::vector<uint32_t> cube_indices = {
    0,  1,  2,  0,  2,  3,  // Front face
    4,  5,  6,  4,  6,  7,  // Back face
    8,  9,  10, 8,  10, 11, // Left face
    12, 13, 14, 12, 14, 15, // Right face
    16, 17, 18, 16, 18, 19, // Top face
    20, 21, 22, 20, 22, 23  // Bottom face
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
        m_vertexArray = std::make_shared<VertexArray>();
        m_vertexArray->bind();
        {
            auto vertexBuffer = std::make_shared<VertexBuffer>(
                cube_vertices.data(), cube_vertices.size() * sizeof(float));
            vertexBuffer->setLayout({
                {ShaderDataType::Float3, "a_position"},
                {ShaderDataType::Float2, "a_texCoord"},
                {ShaderDataType::Float3, "a_normal"},
            });
            m_vertexArray->addVertexBuffer(vertexBuffer);

            auto indexBuffer = std::make_shared<IndexBuffer>(static_cast<uint32_t *>(cube_indices.data()),
                                                             cube_indices.size()); 

            m_vertexArray->setIndexBuffer(indexBuffer);
        }
        m_vertexArray->unbind();

        // 创建Shader
        std::string vertexShaderSource   = FileUtils::ReadFile(SHADER_DIR "00/03_camera.vert");
        std::string fragmentShaderSource = FileUtils::ReadFile(SHADER_DIR "00/03_camera.frag");

        m_shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource, false);

        // 加载纹理
        m_texture = std::make_shared<Texture>(TEXTURE_DIR "wood.png");

        // 设置纹理单元
        m_shader->bind();
        m_shader->setUniformInt("u_texture_0", 0);

        // 创建摄像机
        m_camera = std::make_shared<Camera>(CameraType::Perspective, 45.0f,
                                            this->getWindowWidth() / this->getWindowHeight(), 0.1f,
                                            100.0f);
        m_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

        m_controller = std::make_shared<TrackballController>(m_camera);
    }

    void onRender() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 渲染
        m_shader->bind();
        m_shader->setUniformMat4("u_worldMatrix", glm::mat4(1.0f));
        m_shader->setUniformMat4("u_viewMatrix", glm::inverse(m_camera->getWorldMatrix()));
        m_shader->setUniformMat4("u_projectionMatrix", m_camera->getProjectionMatrix());
        m_texture->bind();

        m_vertexArray->bind();
        glDrawElements(GL_TRIANGLES, cube_indices.size(), GL_UNSIGNED_INT, nullptr);
    }

  private:
    std::shared_ptr<VertexArray> m_vertexArray;

    std::shared_ptr<Shader> m_shader;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Camera> m_camera;

    std::shared_ptr<EventObserver> m_observer;
    std::shared_ptr<TrackballController> m_controller;
};

} // namespace Wave

Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }