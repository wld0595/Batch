#version 330 core

in vec2 v_texCoords;

out vec3 color;

uniform sampler2D u_texture;

void main(){

	vec3 tempcolor=texture(u_texture,v_texCoords).rgb;

	float gray = (tempcolor.r + tempcolor.g + tempcolor.b) / 3.0;

	color = vec3(gray);
}