#pragma once

#include <glad/glad.h>

#include "ecs/scene.hpp"
#include "ecs/wave_system.hpp"
#include "ecs/components/mesh_component.hpp"
#include "ecs/components/camera_component.hpp"
#include "ecs/components/material_component.hpp"
#include "ecs/components/transform_component.hpp"

#include "render/renderer.hpp"

namespace Wave
{
class ForwardRenderSystem : public WaveSystem
{
  public:
    ForwardRenderSystem() {}
    ~ForwardRenderSystem() {}

    void onUpdate(float deltaTime, Scene *scene) override
    {
        auto &reg = scene->getRegistry();

        auto cameraView = reg.view<CameraComponent>();
        for (auto &entity : cameraView)
        {
            auto cameraComp = cameraView.get<CameraComponent>(entity);
            renderScene(scene, cameraComp, deltaTime);
        }
    }

    void renderScene(Scene *scene, CameraComponent &cameraComp, float deltaTime)
    {
        Renderer::Clear();

        auto &reg         = scene->getRegistry();
        auto renderObject = reg.view<MeshComponent, MaterialComponent, TransformComponent>();

        for (auto &entity : renderObject)
        {
            auto waveEntity    = scene->getWaveEntity(entity);
            auto meshComp      = renderObject.get<MeshComponent>(entity);
            auto materialComp  = renderObject.get<MaterialComponent>(entity);
            auto transformComp = renderObject.get<TransformComponent>(entity);

            if (materialComp.renderParams.visible == false) continue;

            applyMaterial(materialComp, cameraComp, transformComp.getWorldMatrix(), deltaTime);
            draw(meshComp, materialComp);
        }
    }

    void applyMaterial(MaterialComponent &materialComp, CameraComponent &cameraComp,
                       const glm::mat4 &worldMatrix, float deltaTime)
    {
        auto shader = materialComp.shader;
        if (shader == nullptr) return;

        shader->setUniformMat4("u_worldMatrix", worldMatrix);
        shader->setUniformMat4("u_cameraWorldInverse", cameraComp.getWorldInverseMatrix());
        shader->setUniformMat4("u_projectionMatrix", cameraComp.getProjectionMatrix());
        shader->setUniformFloat3("u_cameraPosition", cameraComp.getCameraPosition());
        shader->setUniformFloat("u_opacity", materialComp.opacity);

        // 深度测试
        if (materialComp.renderParams.depthTest)
        {
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(static_cast<GLenum>(materialComp.renderParams.depthFunc));
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }

        // 深度写入
        glDepthMask(materialComp.renderParams.depthWrite);

        // 面剔除;
        glCullFace(static_cast<GLenum>(materialComp.renderParams.cullFace));

        switch (materialComp.materialType)
        {
            case MaterialType::Basic:
            {
                shader->setUniformFloat3("u_color", materialComp.color);

                if (materialComp.diffuseMap)
                {
                    materialComp.diffuseMap->bind(materialComp.slot);
                    shader->setUniformInt("u_diffuseMap", materialComp.slot);
                    materialComp.slot++;
                }

                break;
            }
            case MaterialType::Phong:
            {
                break;
            }
            case MaterialType::PBR:
            {
                break;
            }
            default:
                break;
        }
    }

    void draw(MeshComponent &meshComp, MaterialComponent &materialComp)
    {
        auto shader = materialComp.shader;
        if (shader == nullptr) return;

        shader->bind();

        auto vao = meshComp.getVertexArray();

        if (vao)
        {
            vao->bind();
            glDrawElements(GL_TRIANGLES, vao->getIndexCount(), GL_UNSIGNED_INT, nullptr);
        }
        else
        {
            LOG_ERROR("{0} no vao", meshComp.getOwner()->getName());
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }
};
} // namespace Wave