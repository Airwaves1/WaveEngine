#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "ecs/components/material_component.hpp"
#include "utils/constans.hpp"

#define RENDERER

namespace Wave
{

struct RenderSpecs
{
    glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.1f);
    GLenum clearBits     = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
};

class Renderer
{
  public:
    static void Clear() { glClear(specs.clearBits); }

    static void SetClearColor(const glm::vec3 &color)
    {
        glClearColor(color.r, color.g, color.b, 1.0f);
    }

    static void SetClearBits(GLenum bits) { specs.clearBits = bits; }

    static void ApplyAlphaBlend(BlendMode mode = BlendMode::None)
    {
        switch (mode)
        {
            case BlendMode::None:
                glDisable(GL_BLEND);
                break;
            case BlendMode::NormalBlend:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            case BlendMode::Additive:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE);
                break;
            case BlendMode::Multiply:
                glEnable(GL_BLEND);
                glBlendFunc(GL_DST_COLOR, GL_ZERO);
                break;
            case BlendMode::AlphaBlend:
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                break;
            default:
                break;
        }
    }

    static RenderSpecs specs;

  private:
    Renderer() = default;
};
} // namespace Wave
