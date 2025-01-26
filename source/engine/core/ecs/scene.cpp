#include "scene.hpp"
#include "node.hpp"
#include "wave_entity.hpp"
#include "wave_system.hpp"

namespace Wave
{
Scene::Scene() {
    m_rootNode = std::make_shared<Node>("Root");
    m_adminEntity = createEntity("AdminEntity");
}
Scene::~Scene()
{
    destroyAllEntities();
    m_rootNode.reset();
    m_entityMap.clear();
}
WaveEntity *Scene::createEntity(const std::string &name)
{
    return createEntity(UUID::Generate(), name);
}
WaveEntity *Scene::createEntity(const UUID &uuid, const std::string &name)
{
    auto enttEntity = m_registry.create();
    m_entityMap.insert({enttEntity, std::make_shared<WaveEntity>(enttEntity, this)});
    m_entityMap[enttEntity]->setName(name.empty() ? "Entity" : name);
    m_entityMap[enttEntity]->setUUID(uuid);
    m_entityMap[enttEntity]->setParent(m_rootNode.get());

    m_entities.push_back(m_entityMap[enttEntity]);

    return m_entityMap[enttEntity].get();
}
std::vector<WaveEntity *> Scene::getWaveEntity(const std::string &name)
{
    std::vector<WaveEntity *> entities;
    for (auto &[enttEntity, waveEntity] : m_entityMap)
    {
        if (waveEntity->getName() == name)
        {
            entities.push_back(waveEntity.get());
        }
    }
    return entities;
}
WaveEntity *Scene::getWaveEntity(const UUID &uuid)
{
    for (auto &[enttEntity, waveEntity] : m_entityMap)
    {
        if (waveEntity->getUUID() == uuid)
        {
            return waveEntity.get();
        }
    }
    return nullptr;
}
WaveEntity *Scene::getWaveEntity(entt::entity entity)
{
    if (m_entityMap.find(entity) != m_entityMap.end())
    {
        return m_entityMap[entity].get();
    }
    return nullptr;
}

void Scene::destroyEntity(WaveEntity *entity)
{
    if (entity == nullptr)
    {
        return;
    }
    m_entityMap.erase(entity->getEntity());
    m_registry.destroy(entity->getEntity());
    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                    [entity](const std::shared_ptr<WaveEntity> &ptr)
                                    { return ptr.get() == entity; }),
                     m_entities.end());
}

void Scene::destroyAllEntities()
{
    m_registry.clear();
    m_entityMap.clear();
    m_entities.clear();
}

void Scene::addSystem(std::shared_ptr<WaveSystem> system, int priority)
{
    m_systemMap.insert({priority, system});
}

void Scene::removeSystem(std::shared_ptr<WaveSystem> system)
{
    for (auto it = m_systemMap.begin(); it != m_systemMap.end(); ++it)
    {
        if (it->second == system)
        {
            m_systemMap.erase(it);
            break;
        }
    }
}

void Scene::updateSystems(float deltaTime)
{
    for (auto [priority, system] : m_systemMap)
    {
        system->onUpdate(deltaTime, this);
    }

    for (auto [priority, system] : m_systemMap)
    {
        system->afterAllSystemsUpdated(deltaTime, this);
    }
}
} // namespace Wave
