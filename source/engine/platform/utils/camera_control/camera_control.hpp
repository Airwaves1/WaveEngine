#pragma once

#include <memory>
#include "render/camera.hpp"



namespace Wave
{
  class EventObserver;
class TrackballController
{
  public:
    TrackballController(std::shared_ptr<Camera> camera, const glm::vec3 &target = glm::vec3(0.0), float distance = 10.0f);

    // 旋转
    void rotate(float deltaX, float deltaY);

    // 缩放
    void zoom(float delta);

    // 平移
    void pan(float deltaX, float deltaY);

    // 设置基本事件响应
    void setupBasicEvent();

    
    void setCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }
    std::shared_ptr<Camera> getCamera() { return m_camera; }

    void setTarget(const glm::vec3 &target) { m_target = target; }
    const glm::vec3 &getTarget() const { return m_target; }

    void setDistance(float distance) { m_distance = distance; }
    float getDistance() const { return m_distance; }

    void setZoomSpeed(float speed) { m_zoomSpeed = speed; }
    float getZoomSpeed() const { return m_zoomSpeed; }

    void setRotateSpeed(float speed) { m_rotateSpeed = speed; }
    float getRotateSpeed() const { return m_rotateSpeed; }

    void setPanSpeed(float speed) { m_panSpeed = speed; }
    float getPanSpeed() const { return m_panSpeed; }

    void setMinDistance(float distance) { m_minDistance = distance; }
    float getMinDistance() const { return m_minDistance; }

    void setMaxDistance(float distance) { m_maxDistance = distance; }
    float getMaxDistance() const { return m_maxDistance; }


  private:
    std::shared_ptr<Camera> m_camera;

    glm::vec3 m_target{0.0};
    float m_distance{10.0f};

    float m_zoomSpeed{0.1f};
    float m_rotateSpeed{0.01f};
    float m_panSpeed{0.01f};

    float m_minDistance{1.0f};
    float m_maxDistance{100.0f};

    glm::vec2 m_lastMousePos{0.0f};

    bool b_isPanning{false}; // 是否正在平移
    bool b_isRotating{false}; // 是否正在旋转

    std::shared_ptr<EventObserver> m_eventObserver;
};

} // namespace Wave