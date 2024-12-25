#include "application/application.hpp"
#include "application/entry_point.hpp"
#include <iostream>

#include "utils/log.hpp"

namespace Wave
{
class Sandbox : public Wave::Application
{
  public:
    Sandbox()
    {

        Log::Init();
        std::cout << "Hello, Sandbox WaveEngine!" << std::endl;

        std::string a = "WaveEngine!";

        LOG_TRACE("Trace Log '{0}'", a);
        LOG_INFO("Trace Log '{0}'", a);
        LOG_WARN("Trace Log '{0}'", a);
        LOG_ERROR("Trace Log '{0}'", a);
    }

    ~Sandbox() { std::cout << "Goodbye, WaveEngine!" << std::endl; }
};
} // namespace Wave
Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }