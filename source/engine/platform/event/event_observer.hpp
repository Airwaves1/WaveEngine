#pragma once

#include "event_dispatcher.hpp"
#include <memory>

namespace Wave
{

class EventObserver : public std::enable_shared_from_this<EventObserver>
{
  public:
    template <typename T> void subscribe(const std::function<void(T &)> &callback)
    {
        auto self = shared_from_this();
        EventDispatcher::GetInstance().addListener<T>(self, callback);
    }
};

} // namespace Wave