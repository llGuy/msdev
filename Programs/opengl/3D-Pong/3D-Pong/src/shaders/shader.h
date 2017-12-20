#ifndef SHADER_HEADER
#define SHADER_HEADER

#include <GL\glew.h>
#include <string>
#include <fstream>
#include <iostream>


class Shader
{
public:
	explicit Shader(GLenum shaderType, 
		const char* fileDirectory)
		: m_shaderType(shaderType)
	{
		ExtractSourceCode(fileDirectory);
	}
public:
	void Compile(void)
	{
		m_shaderID = glCreateShader(m_shaderType);

		const char* srcs[1];
		srcs[0] = m_src.c_str();
		glShaderSource(m_shaderID, 1, srcs, 0);

		glCompileShader(m_shaderID);
	}
	unsigned int ShaderID(void)
	{
		return m_shaderID;
	}
private:
	void ExtractSourceCode(const char* fileDirectory)
	{
		std::ifstream file(fileDirectory);

		if (!file.good())
		{
			std::cout << "file failed to load... " << fileDirectory;
		}

		m_src = std::string(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>()
		);
	}
private:
	GLenum m_shaderType;
	unsigned int m_shaderID;
	std::string m_src;
};

#endif