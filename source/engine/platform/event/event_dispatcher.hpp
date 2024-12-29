#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <typeindex>
#include "event.hpp"

namespace Wave
{
class EventDispatcher
{
  public:
    using EventCallback = std::function<void(Event &)>; // 事件回调函数, 传入一个Event对象

    struct Handler
    {
        std::weak_ptr<void> owner;
        EventCallback callback;

        Handler(std::weak_ptr<void> owner, EventCallback callback)
            : owner(owner), callback(callback)
        {
        }
    };

    static EventDispatcher &GetInstance()
    {
        static EventDispatcher instance;
        return instance;
    }

    ~EventDispatcher() { m_eventHandlers.clear(); }

    template <typename T>
    void addListener(const std::shared_ptr<void> &owner, const std::function<void(T &)> &callback)
    {
        static_assert(std::is_base_of<Event, T>::value, "T must be derived from Event");

        auto &handlers = m_eventHandlers[typeid(T)];
        handlers.emplace_back(owner,
                              [callback](Event &event) { callback(static_cast<T &>(event)); });
    }

    void removeListener(const std::shared_ptr<void> &owner)
    {
        for (auto &[type, handler] : m_eventHandlers)
        {
            handler.erase(std::remove_if(handler.begin(), handler.end(), [owner](const Handler &h)
                                         { return h.owner.expired() || h.owner.lock() == owner; }),
                          handler.end());
        }
    }

    void dispatch(Event &event)
    {
        auto it = m_eventHandlers.find(typeid(event));
        if (it != m_eventHandlers.end())
        {
            for (auto &handler : it->second)
            {
                if (auto owner = handler.owner.lock())
                {
                    handler.callback(event);
                }
            }
        }
    }

    const std::unordered_map<std::type_index, std::vector<Handler>> &getEventHandlers() const
    {
        return m_eventHandlers;
    }

  private:
    std::unordered_map<std::type_index, std::vector<Handler>> m_eventHandlers;

    EventDispatcher() = default;
};

} // namespace Wave
