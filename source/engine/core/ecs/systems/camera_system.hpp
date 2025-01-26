#pragma once

#include "ecs/wave_system.hpp"
#include "ecs/scene.hpp"

#include "ecs/components/camera_component.hpp"
#include "ecs/components/transform_component.hpp"

namespace Wave
{
class CameraSystem : public WaveSystem
{
  public:
    void onUpdate(float deltaTime, Scene *scene) override
    {
        auto &reg = scene->getRegistry();
        auto view = reg.view<TransformComponent, CameraComponent>();

        for(auto &entity: view)
        {
          auto &transformComp = view.get<TransformComponent>(entity);
          auto & cameraComp = view.get<CameraComponent>(entity);

          cameraComp.updateProjectionMatrix();

          const glm::mat4 &worldMatrix = transformComp.getWorldMatrix();

          cameraComp.setWorldInverseMatrix(glm::inverse(worldMatrix));

          cameraComp.updateProjectionMatrix();

          cameraComp.m_position = transformComp.getPosition();
        }
    }

  private:
};

} // namespace Wave
