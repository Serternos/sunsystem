#version 330 core
layout(location = 0) in vec3 position;
out vec4 vposition;
uniform mat4 MVP;
void main()
{
	vposition = vec4(position, 1.0f);
	gl_Position = MVP * vec4(position, 1.0);
}
