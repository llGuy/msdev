#version 430

in layout(location = 0) vec3 aM_vertexPosition;
in layout(location = 1) vec3 aM_vertexColor;
//in layout(location = 2) vec3 aM_vertexNormal;

//uniform mat4 u_modelTransformMatrix;
uniform mat4 u_mvp;						//model view projection matrix

out vec3 f_color;

void main()
{
	gl_Position = u_mvp * vec4(aM_vertexPosition, 1.0);
	f_color = aM_vertexColor;
}