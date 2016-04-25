#version 330 core

in vec3 a_position;
in vec2 a_texCoord0;

out vec2 v_texCoords;
uniform mat4 u_projTrans;

void main(){	

	gl_Position =  u_projTrans * vec4(a_position,1);

	v_texCoords = a_texCoord0;
}

