#pragma once

#include <vector>
#include <string>
#include <functional>

#include "utils/uuid.hpp"

namespace Wave
{
class Node
{
  public:
    Node() : m_uuid(UUID::Generate()), m_parent(nullptr) {}
    Node(const std::string &name) : m_uuid(UUID::Generate()), m_name(name), m_parent(nullptr) {}

    virtual ~Node() = default;

    bool hasParent();
    bool hasChildren();
    void addChild(Node *child);
    void removeChild(Node *child, std::function<void(Node *)> onRemoved = nullptr);
    void setParent(Node *parent);

    Node *getParent() const { return m_parent; }
    const std::vector<Node *> &getChildren() const { return m_children; }

    const UUID &getUUID() const { return m_uuid; }
    const std::string &getName() const { return m_name; }
    void setName(const std::string &name) { m_name = name; }
    void setUUID(const UUID &uuid) { m_uuid = uuid; }

    void traverse(std::function<void(Node *)> callback);

    void printHierarchy();

  protected:
    UUID m_uuid;
    std::string m_name = "";
    Node *m_parent     = nullptr;
    std::vector<Node *> m_children;
};

} // namespace Wave