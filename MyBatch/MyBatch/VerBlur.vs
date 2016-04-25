#version 330 core

in vec3 vertexPosition_modelspace;
in vec2 vertexUV;

out vec2 UV;
uniform mat4 MVP;

void main(){	

	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	UV = vertexUV;
}



