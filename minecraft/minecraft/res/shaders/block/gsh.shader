#version 430

layout(points) in;
layout(points, max_vertices = 1) out;

in vec3 pass_world_position[];

void main()
{
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	EndPrimitive();
}