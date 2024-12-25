#pragma once
#include <iostream>
#include "application.hpp"

extern Wave::Application* CreateWaveEngineApplication();

int main(int argc, char** argv)
{
    std::cout << "Hello, WaveEngine! " << std::endl;

    auto app = CreateWaveEngineApplication();

    app->start(argc, argv);

    app->mainLoop();

    app->quit();

    delete app;

    return EXIT_SUCCESS;
}