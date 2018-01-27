#version 430

in layout(location = 0) vec3 aM_vertexPosition;
in layout(location = 1) vec3 aM_vertexColor;
//in layout(location = 2) vec3 aM_vertexNormal;

//uniform mat4 u_modelTransformMatrix;
uniform mat4 u_mvp;						//model view projection matrix

uniform mat4 u_projectionMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;

out vec3 pass_colour;
out vec3 pass_worldPosition;
out float visibility;

const float density = 0.007;
const float gradient = 1.5;

void main()
{
	vec4 world_pos = vec4(aM_vertexPosition, 1.0);
	pass_worldPosition = vec3(world_pos.x, world_pos.y, world_pos.z);
	vec4 view_pos = u_viewMatrix * world_pos;
	gl_Position = u_projectionMatrix * view_pos;
	pass_colour = aM_vertexColor;

	vec4 relativeToCameraPosition = u_viewMatrix * vec4(aM_vertexPosition, 1.0);
	float distance = length(relativeToCameraPosition.xyz);
	visibility = exp(-pow((distance * density), gradient));
	visibility = clamp(visibility, 0.0, 1.0);
}