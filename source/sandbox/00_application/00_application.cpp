#include <iostream>
#include "application/application.hpp"
#include "application/entry_point.hpp"

#include "utils/log.hpp"
#include "event/event_dispatcher.hpp"
#include "event/event_observer.hpp"

namespace Wave
{
class EventTest : public Event
{
  public:
    EventTest(std::string name) : m_name(name) {}

    std::string getType() const override { return "EventTest"; }

    const std::string& getName() { return m_name; }

  private:
    std::string m_name;
};

class Sandbox : public Wave::Application
{
  public:
    Sandbox() {}
    ~Sandbox() {}

  protected:
    void onConfigurate(ApplicationConfig &config) override
    {
        config.width  = 1400;
        config.height = 800;
        config.title  = "Wave Engine Sandbox";
    }

    void onInit() override
    {
        LOG_INFO("Sandbox Application is running!");

        m_eventObserver = std::make_shared<EventObserver>();

        m_eventObserver->subscribe<EventTest>([this](EventTest &event) {
            LOG_INFO("EventTest: {0}", event.getName());
        });


        EventTest event("Sandbox EventTest");
        EventDispatcher::GetInstance().dispatch(event);
    }

  private:
    std::shared_ptr<EventObserver> m_eventObserver;
};
} // namespace Wave
Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }