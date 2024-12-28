#version 460 core

out vec4 FragColor;

in vec2 v_uv;

uniform sampler2D u_texture_0;

void main() {
    // FragColor = vec4(0.0, vec2(v_uv.x, v_uv.y), 1.0);
    FragColor = texture(u_texture_0, v_uv);
}