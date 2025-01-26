#include "wave_engine.hpp"
#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "game_framework/game_framework.hpp"
namespace Wave
{
class Sandbox : public Application
{
  public:
    Sandbox() {}
    ~Sandbox() {}

  protected:
    void onConfigurate(ApplicationConfig &config) override
    {
        config.width  = 1400;
        config.height = 800;
        config.title  = "Wave Engine Sandbox";
    }

    void onInit() override
    {
        auto scene = this->getScene();

        // camera
        auto cameraEntity = scene->createEntity("main_camera");
        cameraEntity->addComponent<CameraComponent>();
        auto &camera_trans = cameraEntity->addComponent<TransformComponent>();
        cameraEntity->addComponent<TrackballController>();
        camera_trans.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));

        std::vector<WaveVertex> vertices_cube;
        std::vector<uint32_t> indices_cube;

        std::vector<WaveVertex> vertices_sphere;
        std::vector<uint32_t> indices_sphere;

        GeometryUtils::CreateCube(vertices_cube, indices_cube);
        GeometryUtils::CreateSphere(vertices_sphere, indices_sphere);

        // entity 1
        auto entity1     = scene->createEntity("cube");
        auto &transform1 = entity1->addComponent<TransformComponent>();
        auto &matComp_1  = entity1->addComponent<MaterialComponent>();
        auto &meshComp_1 = entity1->addComponent<MeshComponent>();

        meshComp_1.setData(vertices_cube, indices_cube);
        matComp_1.setMaterialType(MaterialType::Basic);
        transform1.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        TextureSpecification spec;
        spec.wrapS = GL_REPEAT;
        spec.wrapT = GL_REPEAT;

        matComp_1.diffuseMap = TEXTURE_LIB.load(TEXTURE_DIR "container2.png", spec, true);

        // entity 2
        auto entity2     = scene->createEntity("sphere");
        auto &transform2 = entity2->addComponent<TransformComponent>();
        auto &matComp_2  = entity2->addComponent<MaterialComponent>();
        auto &meshComp_2 = entity2->addComponent<MeshComponent>();

        meshComp_2.setData(vertices_sphere, indices_sphere);
        matComp_2.setMaterialType(MaterialType::Basic);
        matComp_2.color = glm::vec3(0.6, 0.5, 0.2);
        matComp_2.diffuseMap = TEXTURE_LIB.load(TEXTURE_DIR "awesomeface.png", spec, true);
 
        // matComp_2.renderParams.visible = false;
        transform2.setPosition(glm::vec3(0.0f, 2.0f, 0.0f));

        scene->addSystem(std::make_shared<TrackballCameraSystem>(), 0);

        glm::vec3 clearColor = glm::vec3(0.4, 0.5, 0.7);
        Renderer::SetClearColor(clearColor);
        // Renderer::SetClearBits(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void onUpdate(float deltaTime) override { getScene()->updateSystems(deltaTime); }

    void onDestory() override
    {
        auto &reg = getScene()->getRegistry();
        auto view = reg.view<TransformComponent>();
        // 打印位置信息
        for (auto entity : view)
        {
            auto waveEntity = getScene()->getWaveEntity(entity);
            auto &transform = view.get<TransformComponent>(entity);
            auto world      = transform.getWorldMatrix();
            LOG_INFO("Entity: {0}, Position: {1}", waveEntity->getName(), glm::to_string(world));
        }
    }

  private:
};

} // namespace Wave

Wave::Application *CreateWaveEngineApplication() { return new Wave::Sandbox(); }