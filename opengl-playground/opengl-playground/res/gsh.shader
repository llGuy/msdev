#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 pass_worldPosition[];
in vec3 pass_colour[];
in float visibility[];

uniform vec3 u_lightPosition;
uniform vec3 u_eyePosition;

out vec3 vertexPosition;
out vec3 color;
out vec3 normal;
out float vis;

vec3 CalculateNormal(int index)
{
	vec3 diffWorldPos1 = normalize(pass_worldPosition[(index + 1) % 3] - pass_worldPosition[index]);
	vec3 diffWorldPos2 = normalize(pass_worldPosition[(index + 2) % 3] - pass_worldPosition[index]);
	return normalize(cross(diffWorldPos1, diffWorldPos2));
}

void main()
{
	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;

		normal = CalculateNormal(i);

		color = pass_colour[i];

		vis = visibility[i];

		vertexPosition = pass_worldPosition[i];

		EmitVertex();
	}
	EndPrimitive();
}