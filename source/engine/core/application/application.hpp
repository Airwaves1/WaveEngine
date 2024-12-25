#pragma once
#include <iostream>
#include <string>   
namespace Wave {
struct ApplicationConfig {
    uint32_t width = 1400;
    uint32_t height = 800;

    std::string title = "Wave Engine";

};

class Application {
public:
  Application();
  Application(const Application &) = delete;
  Application &operator=(const Application &) = delete;
  virtual ~Application();

  void start(int argc, char **argv);
  void mainLoop();
  void quit();
  
};

} // namespace Wave
