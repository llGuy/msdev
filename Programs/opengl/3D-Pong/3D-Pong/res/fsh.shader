#version 430

in vec3 color;

out vec4 newColor;

void main()
{
	newColor = vec4(color, 1.0f);
}