#ifndef SHPROGRAM_HEADER
#define SHPROGRAM_HEADER

#include "shader.h"
#include <iostream>

class SHProgram
{
public:
	explicit SHProgram(const char* vfile, const char* ffile)
		: m_vsh(GL_VERTEX_SHADER, vfile), 
		  m_fsh(GL_FRAGMENT_SHADER, ffile)
	{
	}
public:
	void Link(void)
	{
		m_vsh.Compile();
		m_fsh.Compile();

		if (!CheckShaderStatus(m_vsh.ShaderID()) || !CheckShaderStatus(m_fsh.ShaderID()))
			return;

		m_programID = glCreateProgram();

		glAttachShader(m_programID, m_vsh.ShaderID());
		glAttachShader(m_programID, m_fsh.ShaderID());

		glBindAttribLocation(m_programID, 0, "vertexPosition");
		glBindAttribLocation(m_programID, 1, "vertexColor");
		
		glLinkProgram(m_programID);

		glDeleteShader(m_vsh.ShaderID());
		glDeleteShader(m_fsh.ShaderID());

		CheckProgramStatus(m_programID);

		glUseProgram(m_programID);
	}
private:
	bool CheckShaderStatus(GLuint shaderID)
	{
		GLint status;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLint infoLogLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* buffer = (GLchar*)alloca(infoLogLength * sizeof(GLchar));
			//GLchar* buffer = new GLchar[infoLogLength];

			GLsizei bufferSize;
			glGetShaderInfoLog(shaderID, infoLogLength * sizeof(GLchar), &bufferSize, buffer);
			std::cout << buffer << std::endl;

			return false;
		}
		return true;
	}
	bool CheckProgramStatus(GLuint programID)
	{
		GLint status;
		glGetProgramiv(programID, GL_LINK_STATUS, &status);
		if (status != GL_TRUE)
		{
			GLint infoLogLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
			GLchar* buffer = (GLchar*)alloca(infoLogLength * sizeof(GLchar));
			//GLchar* buffer = new GLchar[infoLogLength];

			GLsizei bufferSize;
			glGetProgramInfoLog(programID, infoLogLength * sizeof(GLchar), &bufferSize, buffer);
			std::cout << buffer << std::endl;

			return false;
		}
		return true;
	}

private:
	Shader m_vsh;
	Shader m_fsh;

	unsigned int m_programID;
};

#endif