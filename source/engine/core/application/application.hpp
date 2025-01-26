#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <chrono>

#include "window/wave_window.hpp"
namespace Wave
{

class Scene;

struct ApplicationConfig
{
    uint32_t width  = 1400;
    uint32_t height = 800;

    std::string title = "Wave Engine";
};

class Application
{
  public:
    Application()                               = default;
    Application(const Application &)            = delete;
    Application &operator=(const Application &) = delete;
    virtual ~Application();

    void start(int argc, char **argv);
    void mainLoop();
    void quit();

    uint32_t getWindowWidth() const { return m_window->getWidth(); }
    uint32_t getWindowHeight() const { return m_window->getHeight(); }

    std::shared_ptr<Scene> getScene() { return m_scene; }

  protected:
    virtual void onConfigurate(ApplicationConfig &config) {}
    virtual void onInit() {}
    virtual void onDestory() {}
    virtual void onUpdate(float deltaTime) {}
    virtual void onRender() {}

    std::chrono::steady_clock::time_point m_lastFrameTimePoint;
    std::chrono::steady_clock::time_point m_startTimePoint;
    uint64_t m_frameIndex = 0;

  private:
    ApplicationConfig m_config;

    bool b_pause = false;

    std::unique_ptr<WaveWindow> m_window;

    std::shared_ptr<Scene> m_scene;
};

} // namespace Wave
