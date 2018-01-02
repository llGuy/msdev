#version 430

in vec3 f_color;

out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(f_color, 1.0f);
}