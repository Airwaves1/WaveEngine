#pragma once

#include "ecs/wave_component.hpp"
#include "ecs/components/transform_component.hpp"

#include <glm/glm.hpp>

namespace Wave
{
class LightComponent : public WaveComponent
{
  public:
    enum class LightType
    {
        Directional, // 方向光
        Point,       // 点光源
        Spot         // 聚光灯
    };

    // 方向光的参数
    struct Directional
    {
    };

    // 点光源的参数
    struct Point
    {
        float constant  = 1.0f; // 衰减系数
        float linear    = 0.09f;
        float quadratic = 0.032f;
    };

    // 聚光灯的参数
    struct Spot
    {
        float cutOff      = glm::cos(glm::radians(12.5f)); // 内部光锥角度
        float outerCutOff = glm::cos(glm::radians(17.5f)); // 外部光锥角度
        float constant    = 1.0f;                          // 衰减系数
        float linear      = 0.09f;
        float quadratic   = 0.032f;
    };

    LightType type; // 灯光类型

    glm::vec3 color = glm::vec3(1.0f); // 灯光颜色

    float intensity = 1.0f; // 灯光强度

    // 根据灯光类型返回对应的参数
    Directional directionalParams;
    Point pointParams;
    Spot spotParams;

    // 更新灯光的位置和方向
    void setPosition(const glm::vec3 &newPosition) { m_position = newPosition; }
    void setDirection(const glm::vec3 &newDirection) { m_direction = newDirection; }

  private:
    // 获取位置和方向（由 TransformComponent 提供）
    glm::vec3 m_position = glm::vec3(0.0f);
    glm::vec3 m_direction = glm::vec3(0.0f);

    friend class LightManagerComponent;
    friend class LightSystem;
};
} // namespace Wave
