#pragma once
#include "ecs/wave_system.hpp"
#include "ecs/scene.hpp"
#include <entt/entt.hpp>

#include "ecs/components/transforms/transform_component.hpp"

namespace Wave
{
class TransformSystem : public WaveSystem
{
  public:
    TransformSystem()  = default;
    ~TransformSystem() = default;

    void onUpdate(float deltaTime, Scene *scene) override
    {
        auto &registry = scene->getRegistry();
        auto view      = registry.view<TransformComponent>();

        for (auto entity : view)
        {
            auto waveEntity = scene->getWaveEntity(entity);
            waveEntity->traverse<WaveEntity>(
                [&](WaveEntity *entity)
                {
                    auto &transform = entity->getComponent<TransformComponent>();
                    updateTransform(transform, entity);
                });
        }
    }

  private:
    void updateTransform(TransformComponent &transform, WaveEntity *entity)
    {
        if (transform.m_dirty)
        {
            transform.m_localMatrix = transform.calculateTransformMatrix();
            transform.m_dirty       = false;
        }

        auto parent = entity->getParentEntity();
        if (parent)
        {
            auto &parentTransform   = parent->getComponent<TransformComponent>();
            transform.m_worldMatrix = parentTransform.m_worldMatrix * transform.m_localMatrix;
        }
        else
        {
            transform.m_worldMatrix = transform.m_localMatrix;
        }
    }
};
} // namespace Wave
