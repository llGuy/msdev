#version 430

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

in vec3 pass_world_position[];
in vec3 pass_texture_types[];

out vec3 normal;
out vec3 texture_coords;
out vec3 vertex_position;

uniform mat4 projection_matrix;
uniform mat4 view_matrix;

vec3 CalculateNormal(vec3 v[3])
{
	vec3 diffWorldPos1 = normalize(v[1] - v[0]);
	vec3 diffWorldPos2 = normalize(v[2] - v[0]);
	return normalize(cross(diffWorldPos1, diffWorldPos2));
}

void GenerateTextureCoordinates(void)
{

}

void CreateVertex(vec3 offset, vec3 n)
{
	vec3 actual_offset = offset * 0.5f;
	vec3 world_position = pass_world_position[0] + actual_offset;

	vec4 view_position = view_matrix * vec4(world_position, 1.0f);

	gl_Position = projection_matrix * view_position;
	
	normal = n;
	//texture_t = pass_texture_types[0];
	vertex_position = world_position;
	EmitVertex();
}

void CreateFaceVertex(vec3 flags, float vcomp1, float vcomp2, unsigned int i)
{
	vec3 v1;
	v1[i] = flags[i];
	v1[(i + 1) % 3] = vcomp1;
	v1[(i + 2) % 3] = vcomp2;
	CreateVertex(v1, flags);
}

void CreateFace(vec3 flags)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (abs(flags[i]) != 0)
		{
			CreateFaceVertex(flags, -1.0f, -1.0f, i);
			CreateFaceVertex(flags, 1.0f, -1.0f, i);
			CreateFaceVertex(flags, -1.0f, 1.0f, i);
			CreateFaceVertex(flags, 1.0f, 1.0f, i);
			EndPrimitive();
			return;
		}
	}
}

void CreateCube(void)
{
	CreateFace(vec3(1.0f, 0.0f, 0.0f));
	CreateFace(vec3(-1.0f, 0.0f, 0.0f));
	CreateFace(vec3(0.0f, 1.0f, 0.0f));
	CreateFace(vec3(0.0f, -1.0f, 0.0f));
	CreateFace(vec3(0.0f, 0.0f, 1.0f));
	CreateFace(vec3(0.0f, 0.0f, -1.0f));
}

void main()
{
	CreateCube();
}