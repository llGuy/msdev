#version 430

in layout(location = 0) vec3 vertex_position;
in layout(location = 1) int texture_type;

out vec3 pass_world_position;
out int pass_texture_types;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform vec3 light_position;
uniform vec3 eye_position;

void main()
{
	pass_world_position = vertex_position;
	gl_Position = vec4(vertex_position, 1.0f);
}