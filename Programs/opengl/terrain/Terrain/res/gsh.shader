#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 pass_worldPosition[];
in vec3 pass_colour[];

uniform vec3 u_lightPosition;

out vec3 vertexPosition;
out vec3 color;
//out vec3 normal;
out float brightness;

void main()
{
	vec3 diffWorldPos1 = pass_worldPosition[1] - pass_worldPosition[0];
	vec3 diffWorldPos2 = pass_worldPosition[2] - pass_worldPosition[0];
	vec3 theNormal = normalize(cross(diffWorldPos1, diffWorldPos2));

	vec3 lightVector = normalize(u_lightPosition - pass_worldPosition[0]);
	float theBrightness = dot(-lightVector, theNormal) / 2;

	for (int i = 0; i < 3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		color = pass_colour[0];
		vertexPosition = pass_worldPosition[i];
	//	vec3 lightVector = normalize(u_lightPosition - vertexPosition);
		brightness = theBrightness;
		EmitVertex();
	}
	EndPrimitive();

}