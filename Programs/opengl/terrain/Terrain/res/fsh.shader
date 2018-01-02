#version 430

in vec3 vertexPosition;
in vec3 color;
//in vec3 normal;
//in vec3 lightVector;
in float brightness;

//uniform vec3 u_lightPosition;

out vec4 fragmentColor;

void main()
{
	vec4 diffuseLight = vec4(brightness, brightness, brightness, 1.0);

	fragmentColor = clamp(diffuseLight, 0, 1) + vec4(color, 1.0f);
}