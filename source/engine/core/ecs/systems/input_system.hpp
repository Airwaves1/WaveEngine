#pragma once

#include "ecs/wave_system.hpp"
#include "ecs/components/singleton_components/input_component.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Wave
{
class InputSystem : public WaveSystem
{
  public:
    InputSystem() = default;

    void onUpdate(float deltaTime, Scene *scene) override
    {
        auto inputComponent = scene->getAdminEntity()->tryGetComponent<InputComponent>();
        if (inputComponent.has_value())
        {
            auto &input = inputComponent.value().get();

            // 更新输入状态的持续时间
            input.updateDurations(deltaTime);


        }
    }

    void afterAllSystemsUpdated(float deltaTime, Scene *scene) override
    {
        auto inputComponent = scene->getAdminEntity()->tryGetComponent<InputComponent>();
        if (inputComponent.has_value())
        {
            auto &input = inputComponent.value().get();

            // 清理一次性输入数据
            input.mouseDelta = glm::vec2(0.0f);
            input.mouseScroll = glm::vec2(0.0f);
        }
    }
};
} // namespace Wave
