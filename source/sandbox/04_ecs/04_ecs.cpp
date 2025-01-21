#include "wave_engine.hpp"
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "ecs/systems/transforms/transform_system.hpp"
#include "ecs/components/transforms/transform_component.hpp"

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
        m_scene      = std::make_shared<Scene>();
        auto entity1 = m_scene->createEntity("character1");
        auto entity2 = m_scene->createEntity("character2");
        entity1->addChild(entity2);

        auto &transform1 = entity1->addComponent<TransformComponent>();
        auto &transform2 = entity2->addComponent<TransformComponent>();

        transform1.setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
        transform2.setPosition(glm::vec3(0.0f, 1.0f, 0.0f));

        m_scene->getRootNode()->printHierarchy();

        m_scene->addSystem(std::make_shared<TransformSystem>());
    }

    void onRender() override {}

    void onUpdate(float deltaTime) override { m_scene->updateSystems(deltaTime); }

    void onDestory() override
    {
        auto &reg = m_scene->getRegistry();
        auto view = reg.view<TransformComponent>();
        // 打印位置信息
        for (auto entity : view)
        {
            auto waveEntity = m_scene->getWaveEntity(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto world = transform.getWorldMatrix();
            LOG_INFO("Entity: {0}, Position: {1}", waveEntity->getName(), glm::to_string(world));
        }
    }

  private:
    std::shared_ptr<Scene> m_scene;
};

} // namespace Wave

Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }