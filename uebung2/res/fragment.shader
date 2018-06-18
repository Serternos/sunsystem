#version 330 core

//light
uniform vec4 light_ambient;
uniform vec4 light_diffuse;
uniform vec4 light_specular;

//material
uniform vec4 mat_emissive = {0.0f, 0.0f, 0.0f, 1.0f};
uniform vec4 mat_ambient = { 0.5f, 0.5f, 0.5f, 1.0f };
uniform vec4 mat_specular = {1.0f, 1.0f, 1.0f, 1.0f};
uniform vec4 mat_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f};
uniform float mat_smoothness = 1.0f;
uniform sampler2D tex_diffuse;
uniform sampler2D tex_emission;

smooth in vec3 view_L;
smooth in vec3 view_normal;
smooth in vec2 texcoord;

out vec4 fragColor;

void main()
{
	vec3 normal = normalize(view_normal);
	vec3 L = normalize(view_L);
	vec3 H = normalize(L + vec3(0.0f, 0.0f, 1.0f));
	vec4 tex_color = texture(tex_diffuse, texcoord);
	float diffuse_intensity = max(dot(normal, L), 0.0f);
	vec4 diffuse = diffuse_intensity * mat_diffuse * light_diffuse; //TODO: replace white with texture
	vec4 ambient = light_ambient * mat_diffuse;
	vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 emission = mat_emissive * texture(tex_emission, texcoord);
	if (diffuse_intensity > 0.0f) {
		float specular_intensity = pow(max(dot(H, normal), 0.0f), mat_smoothness);
		specular = specular_intensity * light_specular * mat_specular * atan(mat_smoothness / 10.0f) * 0.5f;
	}

	fragColor = mix(ambient + emission + specular, diffuse + ambient + specular, diffuse_intensity) * tex_color;
}