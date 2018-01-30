#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

in vec3 pass_world_position[];

out vec3 normal;
out vec3 vertex_position;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

vec3 CalculateNormal(vec3 v[3])
{
	vec3 diffWorldPos1 = normalize(v[1] - v[0]);
	vec3 diffWorldPos2 = normalize(v[2] - v[0]);
	return normalize(cross(diffWorldPos1, diffWorldPos2));
}
void CreateVertex(vec3 offset, vec3 v[3])
{
	vec3 actual_offset = offset * 0.5f;
	vec3 world_position = pass_world_position[0] + actual_offset;

	vec4 view_position = view_matrix * vec4(world_position, 1.0f);

	gl_Position = projection_matrix * view_position;
	vec3 inormal = CalculateNormal(v);
	if ((isinf(inormal.x) || isinf(inormal.y) || isinf(inormal.y)) || 
		(isnan(inormal.x) || isnan(inormal.y) || isnan(inormal.z)))
		normal = vec3(0.0f, 1.0f, 0.0f);
	else normal = inormal;
	vertex_position = world_position;
	EmitVertex();
}


void main()
{
	vec3 v1s[3] = {
		vec3(-1.0, 1.0, 1.0),
		vec3(-1.0, -1.0, 1.0),
		vec3(1.0, 1.0, 1.0)
	};
	CreateVertex(vec3(-1.0, 1.0, 1.0), v1s);
	CreateVertex(vec3(-1.0, -1.0, 1.0), v1s);
	CreateVertex(vec3(1.0, 1.0, 1.0), v1s);
	CreateVertex(vec3(1.0, -1.0, 1.0), v1s);

	EndPrimitive();

	vec3 v2s[3] = {
		vec3(1.0, 1.0, 1.0),
		vec3(1.0, -1.0, 1.0),
		vec3(1.0, 1.0, -1.0)
	};

	CreateVertex(vec3(1.0, 1.0, 1.0), v2s);
	CreateVertex(vec3(1.0, -1.0, 1.0), v2s);
	CreateVertex(vec3(1.0, 1.0, -1.0), v2s);
	CreateVertex(vec3(1.0, -1.0, -1.0), v2s);

	EndPrimitive();

	vec3 v3s[3] = {
		vec3(1.0, 1.0, -1.0),
		vec3(1.0, -1.0, -1.0),
		vec3(-1.0, 1.0, -1.0)
	};

	CreateVertex(vec3(1.0, 1.0, -1.0), v3s);
	CreateVertex(vec3(1.0, -1.0, -1.0), v3s);
	CreateVertex(vec3(-1.0, 1.0, -1.0), v3s);
	CreateVertex(vec3(-1.0, -1.0, -1.0), v3s);

	EndPrimitive();

	vec3 v4s[3] = {
		vec3(-1.0, 1.0, -1.0),
		vec3(-1.0, -1.0, -1.0),
		vec3(-1.0, 1.0, 1.0)
	};

	CreateVertex(vec3(-1.0, 1.0, -1.0), v4s);
	CreateVertex(vec3(-1.0, -1.0, -1.0), v4s);
	CreateVertex(vec3(-1.0, 1.0, 1.0), v4s);
	CreateVertex(vec3(-1.0, -1.0, 1.0), v4s);

	EndPrimitive();

	vec3 v5s[3] = {
		vec3(1.0, 1.0, 1.0),
		vec3(1.0, 1.0, -1.0),
		vec3(-1.0, 1.0, 1.0)
	};

	CreateVertex(vec3(1.0, 1.0, 1.0), v5s);
	CreateVertex(vec3(1.0, 1.0, -1.0), v5s);
	CreateVertex(vec3(-1.0, 1.0, 1.0), v5s);
	CreateVertex(vec3(-1.0, 1.0, -1.0), v5s);

	EndPrimitive();

	vec3 v6s[3] = {
		vec3(-1.0, -1.0, 1.0),
		vec3(-1.0, -1.0, -1.0),
		vec3(1.0, -1.0, 1.0)
	};

	CreateVertex(vec3(-1.0, -1.0, 1.0), v6s);
	CreateVertex(vec3(-1.0, -1.0, -1.0), v6s);
	CreateVertex(vec3(1.0, -1.0, 1.0), v6s);
	CreateVertex(vec3(1.0, -1.0, -1.0), v6s);

	EndPrimitive();
}