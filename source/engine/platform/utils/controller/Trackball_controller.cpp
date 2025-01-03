#include "Trackball_controller.hpp"

#include "event/event.hpp"
#include "event/event_observer.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Wave
{
TrackballController::TrackballController(std::shared_ptr<Camera> camera, const glm::vec3 &target,
                                         float distance)
    : m_camera(camera), m_target(target), m_distance(distance)
{
    m_eventObserver = std::make_shared<EventObserver>();
    setupBasicEvent();
}

void TrackballController::rotate(float deltaX, float deltaY)
{
    glm::vec3 dir  = m_camera->getPosition() - m_target;
    float distance = glm::length(dir);

    // 计算旋转角度
    glm::vec3 right = m_camera->getRightDirection();
    glm::vec3 up    = m_camera->getUpDirection();

    glm::quat rot =
        glm::angleAxis(-deltaY * m_rotateSpeed, right) * glm::angleAxis(deltaX * m_rotateSpeed, up);

    // 计算新的相机位置
    dir = glm::normalize(glm::rotate(rot, dir));
    m_camera->setPosition(m_target + dir * distance);

    // 计算新的相机旋转量
    glm::quat newRot = glm::normalize(rot * m_camera->getRotation());
    m_camera->setRotation(newRot);
}

void TrackballController::zoom(float delta)
{
    float distance = glm::distance(m_camera->getPosition(), m_target);
    distance -= delta * m_zoomSpeed;

    // 限制缩放范围
    distance = glm::clamp(distance, m_minDistance, m_maxDistance);

    // 计算新的相机位置
    glm::vec3 dir = glm::normalize(m_camera->getPosition() - m_target);
    m_camera->setPosition(m_target + dir * distance);
}

void TrackballController::pan(float deltaX, float deltaY)
{
    glm::vec3 dir  = m_camera->getPosition() - m_target;
    // float distance = glm::length(dir);

    // 计算平移距离
    glm::vec3 right = m_camera->getRightDirection();
    glm::vec3 up    = m_camera->getUpDirection();

    glm::vec3 pan = -right * deltaX * m_panSpeed + up * deltaY * m_panSpeed;

    // 计算新的相机位置
    m_camera->setPosition(m_camera->getPosition() + pan);
    m_target += pan;
}

void TrackballController::setupBasicEvent()
{
    if (m_eventObserver == nullptr)
    {
        m_eventObserver = std::make_shared<EventObserver>();
    }

    m_eventObserver->subscribe<MouseButtonPressEvent>(
        [this](const MouseButtonPressEvent &e)
        {
            if (e.getButton() == GLFW_MOUSE_BUTTON_RIGHT)
            {
                b_isRotating = true;
                b_isPanning  = false;
            }
            if (e.getButton() == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                b_isPanning  = true;
                b_isRotating = false;
            }
            m_lastMousePos = glm::vec2(e.getX(), e.getY());
        });

    m_eventObserver->subscribe<MouseButtonReleaseEvent>(
        [this](const MouseButtonReleaseEvent &e)
        {
            if (e.getButton() == GLFW_MOUSE_BUTTON_RIGHT)
            {
                b_isRotating = false;
            }
            if (e.getButton() == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                b_isPanning = false;
            }
        });

    m_eventObserver->subscribe<MouseMoveEvent>(
        [this](const MouseMoveEvent &e)
        {
            if (b_isRotating)
            {
                float deltaX = e.getX() - m_lastMousePos.x;
                float deltaY = e.getY() - m_lastMousePos.y;
                rotate(deltaX, deltaY);
                m_lastMousePos = glm::vec2(e.getX(), e.getY());
            }
            if (b_isPanning)
            {
                float deltaX = e.getX() - m_lastMousePos.x;
                float deltaY = e.getY() - m_lastMousePos.y;
                pan(deltaX, deltaY);
                m_lastMousePos = glm::vec2(e.getX(), e.getY());
            }
            m_lastMousePos = glm::vec2(e.getX(), e.getY());
        });

    m_eventObserver->subscribe<MouseScrollEvent>([this](const MouseScrollEvent &e)
                                                 { zoom(e.getYOffset()); });
}

} // namespace Wave