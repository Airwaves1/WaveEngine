#pragma once

#include "wave_entity.hpp"

namespace Wave
{
class WaveComponent
{
  public:
    enum class WaveComponentType
    {
      Normal,
      Singleton
    };

    WaveComponent()          = default;
    virtual ~WaveComponent() = default;

    WaveEntity *getOwner() const { return m_owner; }
    void setOwner(WaveEntity *owner) { m_owner = owner; }

  protected:
    WaveEntity *m_owner{nullptr};
    WaveComponentType type = WaveComponentType::Normal;

    friend class Scene;
};
} // namespace Wave
