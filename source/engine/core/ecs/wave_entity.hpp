#pragma once

/**
 * 实体类，用于包装entt库的实体，组件相关操作
 */

#include <entt/entity/entity.hpp>
#include <assert.h>

#include "node.hpp"
#include "scene.hpp"

namespace Wave
{
class WaveEntity : public Node
{
  public:
    WaveEntity(entt::entity entity, Scene *scene) : m_entity(entity), m_scene(scene) {}
    ~WaveEntity() = default;

    bool operator==(const WaveEntity &other) const
    {
        return (m_entity == other.m_entity) && (m_scene == other.m_scene);
    }

    bool operator!=(const WaveEntity &other) const
    {
        return !(*this == other);
    }

    entt::entity getEntity() const { return m_entity; }

    Scene *getScene() const { return m_scene; }

    template <typename T, typename... Args>
    T &addComponent(Args &&...args)
    {
        T& component = m_scene->m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
        component.setOwner(this);
        return component;
    }

    template <typename T>
    bool hasComponent()
    {
        return m_scene->m_registry.any_of<T>(m_entity);
    }

    template <typename... TA>
    bool hasAnyComponent()
    {
        return m_scene->m_registry.any_of<TA...>(m_entity);
    }

    template <typename... TA>
    bool hasAllComponents()
    {
        return m_scene->m_registry.all_of<TA...>(m_entity);
    }

    template <typename T>
    T &getComponent()
    {
        assert(hasComponent<T>() && "Entity does not have component!");
        return m_scene->m_registry.get<T>(m_entity);
    }

    template <typename T>
    void removeComponent()
    {
        assert(hasComponent<T>() && "Entity does not have component!");
        m_scene->m_registry.remove<T>(m_entity);
    }

    WaveEntity *getParentEntity()
    {
        auto parent = getParent();
        if (parent)
        {
            return m_scene->getWaveEntity(parent->getUUID());
        }
        return nullptr;
    }

    std::vector<WaveEntity *> getChildrenEntities()
    {
        std::vector<WaveEntity *> res;

        auto childrenNode = getChildren();
        for(auto child : childrenNode)
        {
            res.push_back(m_scene->getWaveEntity(child->getUUID()));
        }

        return res;
    }

  private:
    entt::entity m_entity;
    Scene *m_scene{nullptr};
};
} // namespace Wave
