#pragma once

#include "ecs/wave_system.hpp"
#include "ecs/wave_component.hpp"
#include "ecs/components/light_component.hpp"

namespace Wave
{
class LightManagerComponent : public WaveComponent
{
  public:
    LightManagerComponent() = default;

    std::vector<LightComponent *> lights;

    void addLight(LightComponent *light)
    {
        lights.push_back(light);
    }

    void removeLight(LightComponent *light)
    {
        auto it = std::find(lights.begin(), lights.end(), light);
        if (it != lights.end())
            lights.erase(it);
    }

    void clearLights()
    {
        lights.clear();
    }

    WaveComponentType getType() const { return m_type; }
  protected:
    WaveComponentType m_type = WaveComponentType::Singleton;
};

} // namespace Wave
