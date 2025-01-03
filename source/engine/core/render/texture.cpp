#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "utils/log.hpp"

namespace Wave
{
Texture::Texture(const std::string &path, const TextureSpecification &spec)
{

    m_spec = spec;
    int width, height, channels;
    stbi_set_flip_vertically_on_load(m_spec.flip);

    uint8_t *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

    if (data == nullptr)
    {
        LOG_ERROR("Failed to load texture: {0}", path);
        return;
    }

    m_width  = width;
    m_height = height;

    if (channels == 3)
    {
        m_spec.internalFormat = m_spec.sRGB ? GL_SRGB : GL_RGB;
        m_spec.format         = GL_RGB;
    }
    else if (channels == 4)
    {
        m_spec.internalFormat = m_spec.sRGB ? GL_SRGB_ALPHA : GL_RGBA;
        m_spec.format         = GL_RGBA;
    }

    // 开辟纹理单元
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);

    // 设置纹理映射
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_spec.wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_spec.wrapT);

    // 设置纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_spec.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_spec.magFilter);

    // 生成纹理
    glTexImage2D(GL_TEXTURE_2D, 0, m_spec.internalFormat, m_width, m_height, 0, m_spec.format,
                 m_spec.type, data);

    // 创建mipmap
    if (m_spec.generateMipmap) glGenerateMipmap(GL_TEXTURE_2D);

    // 释放资源
    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_handle == 0)
    {
        LOG_ERROR("Failed to create texture: {0}", path);
    }
}

Texture::~Texture()
{
    if (m_handle != 0)
    {
        glDeleteTextures(1, &m_handle);
    }
}

void Texture::bind(uint32_t slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

} // namespace Wave
