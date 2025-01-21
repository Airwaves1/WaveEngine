#pragma once

#include "wave_entity.hpp"

namespace Wave
{
class WaveComponent
{
  public:
    WaveComponent() = default;
    virtual ~WaveComponent() = default;

    WaveEntity *getOwner() const { return m_owner; }
    void setOwner(WaveEntity *owner) { m_owner = owner; }
  protected:
    WaveEntity *m_owner{nullptr};
};
} // namespace Wave
