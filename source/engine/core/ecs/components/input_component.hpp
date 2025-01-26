#pragma once

#include "ecs/wave_component.hpp"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Wave
{
class InputComponent : public WaveComponent
{
  public:
    enum class MouseButton
    {
        Left   = 0,
        Right  = 1,
        Middle = 2
    };

    // 鼠标输入
    bool b_mousePressed[3]  = {false, false, false}; // 按钮状态
    glm::vec2 mousePosition = {0.0f, 0.0f};          // 鼠标位置
    glm::vec2 mouseDelta    = {0.0f, 0.0f};          // 鼠标移动差值

    // 键盘输入
    bool b_keyPressed[GLFW_KEY_LAST] = {false}; // 键盘按键状态;

    // 设置鼠标状态
    void setMousePressed(MouseButton button, bool pressed)
    {
        b_mousePressed[static_cast<int>(button)] = pressed;
    }

    // 设置鼠标位置
    void setMousePosition(glm::vec2 position) { mousePosition = position; }

    // 设置鼠标移动差值
    void setMouseDelta(glm::vec2 delta) { mouseDelta = delta; }

    // 设置键盘按键状态
    void setKeyPressed(int key, bool pressed)
    {
        if (key >= 0 && key < GLFW_KEY_LAST)
        {
            b_keyPressed[key] = pressed;
        }
    }
};
} // namespace Wave
