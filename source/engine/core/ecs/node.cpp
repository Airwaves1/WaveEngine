#include "node.hpp"
#include <iostream>

namespace Wave
{
bool Node::hasParent() { return m_parent != nullptr; }

bool Node::hasChildren() { return !m_children.empty(); }

void Node::addChild(Node *child)
{
    if(child == m_parent)
    {
        return;
    }

    if(child == this)
    {
        return;
    }

    if (child->hasParent())
    {
        child->getParent()->removeChild(child);
    }

    child->m_parent = this;
    this->m_children.push_back(child);
}

void Node::removeChild(Node *child, std::function<void(Node *)> onRemoved)
{
    if (!hasChildren())
    {
        return;
    }

    auto it = std::find(m_children.begin(), m_children.end(), child);
    if (it != m_children.end())
    {
        m_children.erase(it);
        if (onRemoved)
        {
            onRemoved(child);
        }
    }
}

void Node::setParent(Node *parent)
{
    parent->addChild(this);
}

void Node::traverse(std::function<void(Node *)> callback)
{
    callback(this);

    for (auto child : m_children)
    {
        child->traverse(callback);
    }
}

void Node::printHierarchy() {
    std::function<void(Node *, int)> print = [&](Node *node, int depth) {
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->getName() << std::endl;

        for (auto child : node->getChildren()) {
            print(child, depth + 1);
        }
    };

    print(this, 0);
}

} // namespace Wave
