#include "wave_engine.hpp"
#include "game_framework.hpp"
#include <glad/glad.h>
#include <vector>

// namespace Wave
// {
// class Sandbox : public Application
// {
//   public:
//     Sandbox() {}
//     ~Sandbox() {}

//   protected:
//     void onConfigurate(ApplicationConfig &config) override
//     {
//         config.width  = 1400;
//         config.height = 1200;
//         config.title  = "Wave Engine Sandbox";
//     }

//     void onInit() override
//     {
//         m_vertexArray = ShapesVAO::CreateSphere();

//         // 创建Shader
//         std::string vertexShaderSource   = FileUtils::ReadFile(SHADER_DIR "00/03_camera.vert");
//         std::string fragmentShaderSource = FileUtils::ReadFile(SHADER_DIR "00/03_camera.frag");

//         m_shader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource, false);

//         // 加载纹理
//         m_texture = std::make_shared<Texture>(TEXTURE_DIR "wood.png");

//         // 设置纹理单元
//         m_shader->bind();
//         // m_shader->setUniformInt("u_texture_0", 0);

//         // 创建摄像机
//         m_camera = std::make_shared<Camera>(CameraType::Perspective, 45.0f,
//                                             this->getWindowWidth() / this->getWindowHeight(), 0.1f,
//                                             100.0f);
//         m_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

//         m_controller = std::make_shared<TrackballController>(m_camera);


//         auto root = std::make_shared<Node>("root");
       
//         auto child_0 = std::make_shared<Node>("child_0");
//         auto child_0_0 = std::make_shared<Node>("child_0_0");
//         auto child_0_1 = std::make_shared<Node>("child_0_1");

//         auto child_1 = std::make_shared<Node>("child_1");
//         auto child_1_0 = std::make_shared<Node>("child_1_0");
//         auto child_1_1 = std::make_shared<Node>("child_1_1");

//         root->addChild(child_0.get());
//         root->addChild(child_1.get());

//         child_0->addChild(child_0_0.get());
//         child_0->addChild(child_0_1.get());

//         child_1->addChild(child_1_0.get());
//         child_1->addChild(child_1_1.get());

//         child_0->addChild(child_1.get());
//         child_0->addChild(child_1_0.get());

//         child_1->addChild(child_0.get());

//         root->printHierarchy();
//         std::cout << "Depth: " << child_1_1->getDepth() << std::endl;
//     }

//     void onRender() override
//     {
//         glClearColor(0.4f, 0.3f, 0.7f, 1.0f);
//         glEnable(GL_DEPTH_TEST);
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//         // 渲染
//         m_shader->bind();
//         m_shader->setUniformMat4("u_worldMatrix", glm::mat4(1.0f));
//         m_shader->setUniformMat4("u_viewMatrix", glm::inverse(m_camera->getWorldMatrix()));
//         m_shader->setUniformMat4("u_projectionMatrix", m_camera->getProjectionMatrix());
//         m_texture->bind();

//         m_vertexArray->bind();
//         glDrawElements(GL_TRIANGLES, m_vertexArray->getIndexCount(), GL_UNSIGNED_INT, nullptr);
//     }

//   private:
//     std::shared_ptr<VertexArray> m_vertexArray;

//     std::shared_ptr<Shader> m_shader;
//     std::shared_ptr<Texture> m_texture;
//     std::shared_ptr<Camera> m_camera;

//     std::shared_ptr<EventObserver> m_observer;
//     std::shared_ptr<TrackballController> m_controller;
// };

// } // namespace Wave

// Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }
Wave::Application *CreateWaveEngineApplication() { return nullptr; }