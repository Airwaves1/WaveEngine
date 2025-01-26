#include "application.hpp"

#include "utils/log.hpp"

#include "ecs/scene.hpp"

#include "ecs/systems/transform_system.hpp"
#include "ecs/systems/camera_system.hpp"
#include "ecs/systems/forward_render_system.hpp"
#include "ecs/systems/input_system.hpp"

#include "ecs/components/singleton_components/input_component.hpp"
namespace Wave
{
Application::~Application() {}
void Application::start(int argc, char **argv)
{
    // 记录开始的时间
    m_startTimePoint = std::chrono::steady_clock::now();

    // 初始化日志
    Log::Init();

    // 配置应用程序
    onConfigurate(m_config);

    // 创建窗口
    m_window = std::make_unique<WaveWindow>(m_config.width, m_config.height, m_config.title);

    // 创建场景
    m_scene = std::make_shared<Scene>();

    m_scene->addSystem(std::make_shared<InputSystem>(), 0);
    m_scene->addSystem(std::make_shared<TransformSystem>(), 0);
    m_scene->addSystem(std::make_shared<CameraSystem>(), 0);
    m_scene->addSystem(std::make_shared<ForwardRenderSystem>(), 1);

    // 初始化管理员实体
    auto adminEntity = m_scene->getAdminEntity();
    adminEntity->addComponent<InputComponent>();

    // 初始化
    onInit();
}

void Wave::Application::quit()
{
    // 销毁
    onDestory();
}

void Wave::Application::mainLoop()
{

    while (!m_window->shouldClose())
    {
        // 处理事件
        m_window->pollEvents();

        // 计算时间
        auto now             = std::chrono::steady_clock::now();
        float deltaTime      = std::chrono::duration<float>(now - m_lastFrameTimePoint).count();
        m_lastFrameTimePoint = now;
        m_frameIndex++;

        // 更新和渲染
        if (!b_pause)
        {
            onUpdate(deltaTime);
            onRender();
        }

        m_window->swapBuffers();
    }
}

} // namespace Wave