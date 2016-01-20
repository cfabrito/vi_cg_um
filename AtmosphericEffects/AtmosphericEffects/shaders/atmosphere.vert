#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vPosition;
out vec3 vColor;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	vPosition = vec3(vec4(projection * view * model * vec4(position, 1)).xyz);
	vColor = normal;
}