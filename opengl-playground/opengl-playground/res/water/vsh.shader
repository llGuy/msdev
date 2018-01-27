#version 430

in layout(location = 0) vec3 aM_vertexPosition;
in layout(location = 1) vec3 aM_vertexColor;

out vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
	vec4 worldPosition = model * vec4(aM_vertexPosition, 1.0f);
	vec4 viewPosition = view * worldPosition;
	gl_Position = projection * viewPosition;

	color = aM_vertexColor;
}