#shader vertex
#version 460 core

in vec4 position;
in vec3 color;

out vec3 v_color;

uniform mat4 u_proj;

void main()
{
	gl_Position = u_proj * position;

	v_color = color;
}