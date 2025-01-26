#pragma once

/**
 * 系统基类，用于处理组件数据
 */

#include "ecs/scene.hpp"

namespace Wave
{
class WaveSystem
{
  public:
    virtual ~WaveSystem() = default;

    virtual void onUpdate(float deltaTime, Scene* scene) = 0;

    virtual void afterAllSystemsUpdated(float deltaTime, Scene* scene) {}

  public:
    int priority = 0;
};

} // namespace Wave
