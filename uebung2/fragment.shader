#version 330 core
out vec4 color;
in vec4 vposition;
void main()
{
	color = vposition;
}