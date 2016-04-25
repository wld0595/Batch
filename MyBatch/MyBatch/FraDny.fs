#version 330 core

in vec2 v_texCoords;

out vec3 color;

uniform sampler2D u_texture;

uniform float time;

void main() {

    vec3 movescale = texture(u_texture, v_texCoords + 0.005 * vec2(sin(v_texCoords.x * 1024.0+time), cos(v_texCoords.y * 768.0 + time))).rgb ;

    color = movescale ;

}