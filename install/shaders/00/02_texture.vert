#version 460 core
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord; // texture coordinates

out vec2 v_uv;
void main()
{
    v_uv = a_texCoord;
    gl_Position = vec4(a_position,1.0f);
}