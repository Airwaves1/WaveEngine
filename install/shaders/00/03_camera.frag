#version 460 core

out vec4 FragColor;

in vec2 v_uv;
in vec3 v_normal;

uniform sampler2D u_texture_0;


void main() {
    vec3 normal = normalize(v_normal) * 0.5 + 0.5; //归一化到0-
    FragColor = vec4(normal, 1.0);
}