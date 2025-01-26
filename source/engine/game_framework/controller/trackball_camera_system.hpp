#pragma once

#include "ecs/wave_system.hpp"
#include "ecs/wave_entity.hpp"
#include "ecs/wave_component.hpp"

#include "game_framework/controller/trackball_controller_component.hpp"
#include "ecs/components/transform_component.hpp"
#include "ecs/components/camera_component.hpp"

#include "event/event.hpp"
#include "event/event_observer.hpp"
#include "ecs/components/singleton_components/input_component.hpp"

#include <GLFW/glfw3.h>

#include "utils/log.hpp"

namespace Wave
{
class TrackballCameraSystem : public WaveSystem
{
  public:
    void onUpdate(float deltaTime, Scene *scene) override
    {
        auto &reg = scene->getRegistry();
        auto view = reg.view<TrackballController, CameraComponent, TransformComponent>();

        for (auto entity : view)
        {
            auto &trackball = view.get<TrackballController>(entity);
            auto &camera    = view.get<CameraComponent>(entity);
            auto &transform = view.get<TransformComponent>(entity);

            if (!trackball.b_useTrackball) continue;

            // 获取输入组件
            auto inputComponent = scene->getAdminEntity()->tryGetComponent<InputComponent>();
            if (!inputComponent.has_value()) continue;

            auto &input = inputComponent.value().get();

            trackball.radius = glm::length(transform.getPosition() - trackball.target);

            // 处理鼠标旋转
            handleRotation(trackball, transform, input);

            // 处理鼠标滚轮缩放
            handleZoom(trackball, transform, input);

            // 处理平移
            handlePan(trackball, transform, input);
        }
    }

  private:
    // 处理围绕目标点旋转
    void handleRotation(TrackballController &trackball, TransformComponent &transform,
                        InputComponent &input)
    {
        if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
        {
            glm::vec2 mouseDelta = input.mouseDelta;
            // glm::vec2 mouseDelta = input.mousePosition - trackball.lastMousePosition;
            if (glm::length(mouseDelta) > 0.0f) // 避免零向量计算
            {
                glm::vec3 dir = transform.getForward();

                glm::vec3 right = transform.getRight();
                glm::vec3 up    = transform.getUp();

                glm::quat rot = glm::angleAxis(-mouseDelta.x * trackball.rotationSpeed, up) *
                                glm::angleAxis(-mouseDelta.y * trackball.rotationSpeed, right);
            
                // 更新位置
                dir = glm::normalize(glm::rotate(rot, dir));
                glm::vec3 newPosition = trackball.target - dir * trackball.radius;
                transform.setPosition(newPosition);

                // 更新旋转
                glm::quat newRotation = glm::normalize(rot * transform.getRotation());
                transform.setRotation(newRotation);
            }
        }
    }

    void handleZoom(TrackballController &trackball, TransformComponent &transform,
                    InputComponent &input)
    {
        float zoomDelta = input.mouseScroll.y; // 鼠标滚轮增量
        if (zoomDelta != 0.0f)
        {
            float newRadius = trackball.radius - zoomDelta * trackball.zoomSpeed;
            newRadius       = glm::clamp(newRadius, trackball.minDistance, trackball.maxDistance);

            glm::vec3 forward     = transform.getForward();
            glm::vec3 newPosition = trackball.target - forward * newRadius;

            transform.setPosition(newPosition);
            trackball.radius = newRadius;
        }
    }

    void handlePan(TrackballController &trackball, TransformComponent &transform,
                   InputComponent &input)
    {
        if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            glm::vec2 mouseDelta = input.mouseDelta;
            if (glm::length(mouseDelta) > 0.0f) // 避免零向量计算
            {
                glm::vec3 right = transform.getRight();
                glm::vec3 up    = transform.getUp();

                glm::vec3 pan = right * -mouseDelta.x + up * mouseDelta.y;
                pan *= trackball.panSpeed;

                glm::vec3 newPosition = transform.getPosition() + pan;
                transform.setPosition(newPosition);

                trackball.target += pan;

                LOG_DEBUG("position x: {0}, y: {1}, z: {2}", newPosition.x, newPosition.y, newPosition.z);
            }
        }
    }

  private:
    std::shared_ptr<EventObserver> m_eventObserver;
};
} // namespace Wave
