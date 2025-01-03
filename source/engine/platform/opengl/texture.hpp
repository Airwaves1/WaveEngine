#pragma once

#include <glad/glad.h>
#include <string>

namespace Wave
{
// 纹理规格
struct TextureSpecification
{
    // 纹理映射
    GLenum wrapS = GL_REPEAT;
    GLenum wrapT = GL_REPEAT;

    // 纹理过滤
    GLenum minFilter = GL_LINEAR; // 缩小的过滤器
    GLenum magFilter = GL_LINEAR; // 放大的过滤器

    // 纹理格式
    GLenum internalFormat = GL_RGBA; // 纹理内部格式
    GLenum format         = GL_RGBA; // 纹理格式

    // 纹理类型
    GLenum type = GL_UNSIGNED_BYTE; // 纹理数据类型

    // 是否生成mipmap
    bool generateMipmap = true;

    // 多重采样
    uint32_t samples = 1;

    // 是否翻转
    bool flip = true;

    // 是否使用sRGB
    bool sRGB = false;
};

class Texture
{
  public:
    Texture(const std::string &path, const TextureSpecification &spec = TextureSpecification());
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind() const;

  private:
    uint32_t m_width, m_height;
    uint32_t m_handle;
    TextureSpecification m_spec;
    std::string m_path;
};
} // namespace Wave
