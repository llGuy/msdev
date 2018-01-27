#version 430

in vec3 vertexPosition;
in vec3 color;
in vec3 normal;
in float vis;

uniform vec3 u_lightPosition;
uniform vec3 u_eyePosition;

out vec4 fragmentColor;

void main()
{
	vec3 lightVector = normalize(u_lightPosition - vertexPosition);

	float brightness = dot(lightVector, normalize(normal)) * 0.8f;
	vec4 diffuseLight = vec4(brightness, brightness, brightness * 0.6f, 1.0);

	vec3 reflectedLightWorld = reflect(-lightVector, normal);
	vec3 eyeVector = normalize(u_eyePosition - vertexPosition);
	float specularity = dot(reflectedLightWorld, eyeVector);
	//specularity = pow(specularity, 3);
	specularity = specularity * specularity * specularity;
	vec4 specularLight = vec4(specularity, specularity, specularity * 0.6f, 1);

	fragmentColor = clamp(diffuseLight, 0, 1) + vec4(color, 1.0) +clamp(specularLight, 0, 1);
	fragmentColor = mix(vec4(vec3(0.0, 0.0, 0.0), 1.0), fragmentColor, vis);
}