#version 430

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexColor;
in layout(location = 2) mat4 transformMatrix;


out vec3 color;

void main()
{
	gl_Position = transformMatrix * vec4(vertexPosition, 1.0f);
	color = vertexColor;
}