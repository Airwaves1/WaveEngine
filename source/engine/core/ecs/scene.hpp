#pragma once

/**
 * 用于组织场景的实体和系统，包装了entt库的注册表，更新系统
 */

#include <entt/entity/registry.hpp>
#include <unordered_map>
#include <map>

#include "utils/uuid.hpp"
namespace Wave
{
class WaveEntity;
class WaveSystem;
class Node;
class Scene
{
  public:
    Scene();
    ~Scene();

    WaveEntity *createEntity(const std::string &name = "");
    WaveEntity *createEntity(const UUID &uuid, const std::string &name = "");

    std::vector<WaveEntity *> getWaveEntity(const std::string &name);
    WaveEntity *getWaveEntity(const UUID &uuid);
    WaveEntity *getWaveEntity(entt::entity entity);

    void destroyEntity(WaveEntity *entity);
    void destroyAllEntities();

    void addSystem(std::shared_ptr<WaveSystem> system, int priority = 0);
    void removeSystem(std::shared_ptr<WaveSystem> system);
    void updateSystems(float deltaTime);

    entt::registry &getRegistry() { return m_registry; }
    Node *getRootNode() { return m_rootNode.get(); }
    const std::string &getName() const { return m_name; }
    const std::vector<std::shared_ptr<WaveEntity>> &getEntities() const { return m_entities; }

    WaveEntity *getAdminEntity() { return m_adminEntity; }

  private:
    std::string m_name;
    entt::registry m_registry;

    std::unordered_map<entt::entity, std::shared_ptr<WaveEntity>> m_entityMap;
    std::vector<std::shared_ptr<WaveEntity>> m_entities;

    std::multimap<int, std::shared_ptr<WaveSystem>> m_systemMap;

    std::shared_ptr<Node> m_rootNode;

    WaveEntity *m_adminEntity = nullptr;

    friend class WaveEntity;
};

} // namespace Wave