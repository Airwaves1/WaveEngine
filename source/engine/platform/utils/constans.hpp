#pragma once

#include <glad/glad.h>

namespace Wave
{
enum class RenderSide
{
    Front        = GL_FRONT,
    Back         = GL_BACK,
    DoubelSide = GL_FRONT_AND_BACK
};

enum class RenderMode
{
    Fill  = GL_FILL,
    Line  = GL_LINE,
    Point = GL_POINT
};

enum class CullFace
{
    Front        = GL_FRONT,
    Back         = GL_BACK,
    FrontAndBack = GL_FRONT_AND_BACK
};

enum class BlendMode
{
    None = 0,
    NormalBlend, // 正常混合
    Additive,        // 加法混合
    Multiply,        // 乘法混合
    AlphaBlend,      // Alpha混合

    // 自定义混合模式：可以直接使用源与目标的混合因子
    CustomBlend = -1 // 特殊，表示需要自定义混合函数
};

enum class DepthFunc
{
    Never        = GL_NEVER,
    Less         = GL_LESS,
    Equal        = GL_EQUAL,
    LessEqual    = GL_LEQUAL,
    Greater      = GL_GREATER,
    NotEqual     = GL_NOTEQUAL,
    GreaterEqual = GL_GEQUAL,
    Always       = GL_ALWAYS
};

enum class StencilFunc
{
    Never        = GL_NEVER,
    Less         = GL_LESS,
    Equal        = GL_EQUAL,
    LessEqual    = GL_LEQUAL,
    Greater      = GL_GREATER,
    NotEqual     = GL_NOTEQUAL,
    GreaterEqual = GL_GEQUAL,
    Always       = GL_ALWAYS
};

enum class StencilOp
{
    Keep          = GL_KEEP,
    Zero          = GL_ZERO,
    Replace       = GL_REPLACE,
    Increment     = GL_INCR,
    IncrementWrap = GL_INCR_WRAP,
    Decrement     = GL_DECR,
    DecrementWrap = GL_DECR_WRAP,
    Invert        = GL_INVERT
};

enum class StencilFace
{
    Front        = GL_FRONT,
    Back         = GL_BACK,
    FrontAndBack = GL_FRONT_AND_BACK
};

enum class BufferBit
{
    Color   = GL_COLOR_BUFFER_BIT,
    Depth   = GL_DEPTH_BUFFER_BIT,
    Stencil = GL_STENCIL_BUFFER_BIT
};

enum class TextureType
{
    Texture2D      = GL_TEXTURE_2D,
    TextureCubeMap = GL_TEXTURE_CUBE_MAP
};

enum class TextureFormat
{
    Red            = GL_RED,
    Rgb            = GL_RGB,
    Rgba           = GL_RGBA,
    DepthComponent = GL_DEPTH_COMPONENT,
    DepthStencil   = GL_DEPTH_STENCIL
};

enum class TextureInternalFormat
{
    Rgb            = GL_RGB,
    Rgba           = GL_RGBA,
    DepthComponent = GL_DEPTH_COMPONENT,
    DepthStencil   = GL_DEPTH_STENCIL
};

enum class TextureDataType
{
    UnsignedByte = GL_UNSIGNED_BYTE,
    Float        = GL_FLOAT
};

enum class TextureWrap
{
    Repeat         = GL_REPEAT,
    MirroredRepeat = GL_MIRRORED_REPEAT,
    ClampToEdge    = GL_CLAMP_TO_EDGE,
    ClampToBorder  = GL_CLAMP_TO_BORDER
};

enum class TextureFilter
{
    Nearest              = GL_NEAREST,
    Linear               = GL_LINEAR,
    NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
    LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
    NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
    LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR
};

enum class TextureAttachment
{
    Color0       = GL_COLOR_ATTACHMENT0,
    Color1       = GL_COLOR_ATTACHMENT1,
    Color2       = GL_COLOR_ATTACHMENT2,
    Color3       = GL_COLOR_ATTACHMENT3,
    Color4       = GL_COLOR_ATTACHMENT4,
    Color5       = GL_COLOR_ATTACHMENT5,
    Color6       = GL_COLOR_ATTACHMENT6,
    Color7       = GL_COLOR_ATTACHMENT7,
    Depth        = GL_DEPTH_ATTACHMENT,
    Stencil      = GL_STENCIL_ATTACHMENT,
    DepthStencil = GL_DEPTH_STENCIL_ATTACHMENT
};

enum class FramebufferStatus
{
    Complete                    = GL_FRAMEBUFFER_COMPLETE,
    Undefined                   = GL_FRAMEBUFFER_UNDEFINED,
    IncompleteAttachment        = GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT,
    IncompleteMissingAttachment = GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT,
    IncompleteDrawBuffer        = GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER,
    IncompleteReadBuffer        = GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER,
    Unsupported                 = GL_FRAMEBUFFER_UNSUPPORTED,
    IncompleteMultisample       = GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE,
    IncompleteLayerTargets      = GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS
};
} // namespace Wave
