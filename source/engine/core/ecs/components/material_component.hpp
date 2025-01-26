#pragma once
#include <glm/glm.hpp>
#include "utils/constans.hpp"
#include "ecs/wave_component.hpp"
#include "opengl/texture.hpp"
#include "utils/uuid.hpp"
#include "opengl/shader.hpp"
#include "resources/shader_lib.hpp"
#include "utils/file_utils.hpp"

namespace Wave
{

enum class MaterialType
{
    None,
    Basic,
    Phong,
    PBR
};

struct MaterialRenderParams
{
    bool wireframe = false; // 是否线框模式

    bool visible = true; // 是否可见

    RenderSide side = RenderSide::Front; // 渲染面

    RenderMode renderMode = RenderMode::Fill; // 渲染模式

    BlendMode blendMode = BlendMode::NormalBlend; // 混合模式

    DepthFunc depthFunc = DepthFunc::Less; // 深度测试函数
    bool depthTest      = true;            // 是否开启深度测试
    bool depthWrite     = true;            // 是否开启深度写入

    CullFace cullFace = CullFace::Back; // 背面剔除

    bool colorWrite = true; // 是否开启颜色写入

    int stencilRef                = 0;     // 模板测试参考值
    unsigned int stencilMask      = 0xFF;  // 模板测试掩码
    unsigned int stencilWriteMask = 0xFF;  // 模板写入掩码
    bool stencilTest              = false; // 是否开启模板测试
    bool stencilWrite             = false; // 是否开启模板写入

    bool polygonOffset        = false; // 是否开启多边形偏移
    float polygonOffsetFactor = 0.0f;  // 多边形偏移因子
    float polygonOffsetUnits  = 0.0f;  // 多边形偏移单位
};

class MaterialComponent : public WaveComponent
{
  public:
    MaterialComponent(MaterialType type = MaterialType::Basic) : uuid(UUID::Generate())
    {
        setMaterialType(type);
    }

    virtual ~MaterialComponent() {}

    void setMaterialType(MaterialType matType)
    {
        if (matType == materialType) return;

        switch (matType)
        {
            case MaterialType::Basic:
            {
                shader       = SHADER_LIB.load("basic", SHADER_DIR "shader_lib/basic.vert",
                                               SHADER_DIR "shader_lib/"
                                                                "basic.frag");
                materialType = matType;
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

    MaterialType materialType = MaterialType::None;

    std::string name = "Material"; // 材质名称

    UUID uuid;

    std::shared_ptr<Shader> shader = nullptr;

    MaterialRenderParams renderParams;

    glm::vec3 color = glm::vec3(0.0f); // 材质颜色

    float metallic  = 0.0f; // 金属度
    float roughness = 0.0f; // 粗糙度
    float ao        = 1.0f; // 环境光遮蔽

    float shininess = 32.0f; // 光泽度

    float opacity    = 1.0f;  // 透明度
    bool transparent = false; // 是否透明

    std::shared_ptr<Texture> diffuseMap   = nullptr; // 漫反射贴图
    std::shared_ptr<Texture> specularMap  = nullptr; // 镜面反射贴图
    std::shared_ptr<Texture> normalMap    = nullptr; // 法线贴图
    std::shared_ptr<Texture> heightMap    = nullptr; // 高度贴图
    std::shared_ptr<Texture> occlusionMap = nullptr; // 环境光遮蔽贴图
    std::shared_ptr<Texture> emissiveMap  = nullptr; // 自发光贴图

  private:
    int slot = 0;

    friend class ForwardRenderSystem;
};
} // namespace Wave