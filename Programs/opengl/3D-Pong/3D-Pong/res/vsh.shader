#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexColor;

out vec3 color;

void main()
{
	gl_Position = vec4(vertexPosition, 0.0);
	color = vertexColor;
}