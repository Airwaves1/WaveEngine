// #pragma once

// #define GLM_ENABLE_EXPERIMENTAL
// #include <glm/glm.hpp>
// #include <glm/gtx/transform.hpp>
// #include <glm/gtc/quaternion.hpp>
// #include "utils/log.hpp"

// namespace Wave
// {
// enum class CameraType_2
// {
//     Perspective,
//     Orthographic
// };

// class Camera
// {
//   public:
//     Camera() = default;
//     Camera(CameraType_2 type, float fov, float aspect, float near, float far)
//         : m_type(type), m_fov(fov), m_aspect(aspect), m_near(near), m_far(far)
//     {
//         b_dirty = true;
//         updateProjectionMatrix();
//         updateWorldMatrix();
//     }

//     const glm::mat4 &getProjectionMatrix()
//     {
//         if (b_dirty)
//         {
//             updateProjectionMatrix();
//         }
//         return m_projectionMatrix;
//     }

//     const glm::mat4 &getWorldMatrix()
//     {
//         if (b_dirty)
//         {
//             updateWorldMatrix();
//         }
//         return m_worldMatrix;
//     }

//     const glm::mat4 getViewProjectionMatrix()
//     {
//         return getProjectionMatrix() * glm::inverse(getWorldMatrix());
//     }

//     void updateProjectionMatrix()
//     {
//         if (m_type == CameraType_2::Perspective)
//         {
//             m_projectionMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
//         }
//         else if (m_type == CameraType_2::Orthographic)
//         {
//             m_projectionMatrix =
//                 glm::ortho(m_orthoLeft, m_orthoRight, m_orthoBottom, m_orthoTop, m_near, m_far);
//         }

//         b_dirty = false;
//     }

//     void updateWorldMatrix()
//     {
//         m_worldMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation);
//         b_dirty       = false;
//     }

//     void setPosition(const glm::vec3 &position)
//     {
//         if (m_position != position)
//         {
//             m_position = position;
//             b_dirty    = true;
//         }
//     }

//     void setRotation(const glm::quat &rotation)
//     {
//         if (m_rotation != rotation)
//         {
//             m_rotation = rotation;
//             b_dirty    = true;
//         }
//     }

//     void setRotation(const glm::vec3 &axis, float angle)
//     {
//         setRotation(glm::angleAxis(angle, glm::normalize(axis)));
//     }

//     void setRotation(const glm::vec3 &euler) { setRotation(glm::quat(euler)); }

//     void setWorldUp(const glm::vec3 &worldUp)
//     {
//         if (m_worldUp != worldUp)
//         {
//             m_worldUp = worldUp;
//             b_dirty   = true;
//         }
//     }

//     void setFov(float fov)
//     {
//         if (m_fov != fov)
//         {
//             m_fov   = fov;
//             b_dirty = true;
//         }
//     }

//     void setAspect(float aspect)
//     {
//         if (m_aspect != aspect)
//         {
//             m_aspect = aspect;
//             b_dirty  = true;
//         }
//     }

//     void setNear(float near)
//     {
//         if (m_near != near)
//         {
//             m_near  = near;
//             b_dirty = true;
//         }
//     }

//     void setFar(float far)
//     {
//         if (m_far != far)
//         {
//             m_far   = far;
//             b_dirty = true;
//         }
//     }

//     void setOrthoLeft(float left)
//     {
//         if (m_orthoLeft != left)
//         {
//             m_orthoLeft = left;
//             b_dirty     = true;
//         }
//     }

//     void setOrthoRight(float right)
//     {
//         if (m_orthoRight != right)
//         {
//             m_orthoRight = right;
//             b_dirty      = true;
//         }
//     }

//     void setOrthoBottom(float bottom)
//     {
//         if (m_orthoBottom != bottom)
//         {
//             m_orthoBottom = bottom;
//             b_dirty       = true;
//         }
//     }

//     void setOrthoTop(float top)
//     {
//         if (m_orthoTop != top)
//         {
//             m_orthoTop = top;
//             b_dirty    = true;
//         }
//     }

//     void setOrthographic(float left, float right, float bottom, float top)
//     {
//         setOrthoLeft(left);
//         setOrthoRight(right);
//         setOrthoBottom(bottom);
//         setOrthoTop(top);
//         b_dirty = true;
//     }

//     void setPerspective(float fov, float aspect, float near, float far)
//     {
//         setFov(fov);
//         setAspect(aspect);
//         setNear(near);
//         setFar(far);
//         b_dirty = true;
//     }

//     const glm::vec3 &getPosition() const { return m_position; }
//     const glm::quat &getRotation() const { return m_rotation; }
//     const glm::vec3 &getWorldUp() const { return m_worldUp; }
//     glm::vec3 getForwardDirection() const
//     {
//         return glm::normalize(m_rotation * glm::vec3(0.0f, 0.0f, -1.0f));
//     }

//     glm::vec3 getRightDirection() const
//     {
//         return glm::normalize(m_rotation * glm::vec3(1.0f, 0.0f, 0.0f));
//     }

//     glm::vec3 getUpDirection() const
//     {
//         return glm::normalize(m_rotation * glm::vec3(0.0f, 1.0f, 0.0f));
//     }

//     float getFov() const { return m_fov; }
//     float getAspect() const { return m_aspect; }
//     float getNear() const { return m_near; }
//     float getFar() const { return m_far; }

//     float getOrthoLeft() const { return m_orthoLeft; }
//     float getOrthoRight() const { return m_orthoRight; }
//     float getOrthoBottom() const { return m_orthoBottom; }
//     float getOrthoTop() const { return m_orthoTop; }

//     const CameraType_2 &getType() const { return m_type; }
//     void setType(CameraType_2 type)
//     {
//         if (m_type != type)
//         {
//             m_type = type;
//             b_dirty = true;
//         }
//     }

//   private:
//     CameraType_2 m_type = CameraType_2::Perspective;

//     glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
//     glm::quat m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

//     glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

//     glm::mat4 m_worldMatrix      = glm::mat4(1.0f);
//     glm::mat4 m_projectionMatrix = glm::mat4(1.0f);

//     bool b_dirty = true; // 脏标记

//     // Perspective
//     float m_fov    = 45.0f;
//     float m_aspect = 1.0f;
//     float m_near   = 0.1f;
//     float m_far    = 100.0f;

//     // Orthographic
//     float m_orthoLeft   = -1.0f;
//     float m_orthoRight  = 1.0f;
//     float m_orthoBottom = -1.0f;
//     float m_orthoTop    = 1.0f;
// };
// } // namespace Wave
