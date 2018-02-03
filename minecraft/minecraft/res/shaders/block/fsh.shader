#version 430

uniform sampler2D diffuse;
uniform vec3 light_position;
uniform vec3 eye_position;

out vec4 fragment_color;

//in int texture_type;
in vec3 normal;
in vec3 vertex_position;

float Diffuse(vec3 light_vector)
{
	float brightness = dot(light_vector, normal);
	return brightness * 0.3f;
}

float Specular(vec3 light_vector)
{
	vec3 reflected_light_world = reflect(-light_vector, normal);
	vec3 eye_vector = normalize(eye_position - vertex_position);
	float specularity = dot(reflected_light_world, eye_vector);
	specularity = specularity * specularity * specularity;
	return specularity;
}

void main()
{
	vec3 light_vector = normalize(light_position - vertex_position);
	float diffuse_brightness = Diffuse(light_vector);
	float specular_brightness = Specular(light_vector);

	vec4 diffuse = vec4(diffuse_brightness, diffuse_brightness, diffuse_brightness, 1.0f);
	vec4 specular = vec4(specular_brightness, specular_brightness, specular_brightness, 1.0f);

	if (isinf(diffuse.r) && isnan(diffuse.r))
		diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	if (isinf(specular.r) && isnan(specular.r))
		specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	fragment_color = clamp(diffuse, 0, 1) + vec4(0.0f, 0.5f, 0.0f, 1.0f) + clamp(specular, 0, 1) * 0.5f;
}