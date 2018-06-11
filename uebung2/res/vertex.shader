#version 330 core

uniform vec3 lightposition = {0.0f, 0.0f, 0.0f}; //light in world space

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 V;

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;

out float lightatt;
smooth out vec3 view_L;
smooth out vec3 view_normal;
smooth out vec2 texcoord;

void main()
{
	vec3 view_position = (MV * vec4(v_position, 1.0f)).xyz;
	vec3 view_lightposition = (V * vec4(lightposition, 1.0f)).xyz;
	view_normal = normalize(MV * vec4(v_normal, 0.0f)).xyz;

	view_L = (view_lightposition - view_position);
	texcoord = v_texcoord;

	gl_Position = MVP * vec4(v_position, 1.0);
}
