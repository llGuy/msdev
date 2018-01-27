#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <string>
#include <GL/glew.h>
#include <stb-master/stb_image.h>

typedef unsigned int tex_id;

class Texture
{	
public:
	explicit Texture(void) = default;
	explicit Texture(const std::string& file)
		: m_file(file)
	{
	}
	void Init(void)
	{
		ImageData id = LoadImageData(m_file);
		SendData(id);
	}
	void Bind(int unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
private:
	struct ImageData
	{
		unsigned char* data;
		unsigned int w;
		unsigned int h;
	};
	ImageData LoadImageData(const std::string& file)
	{
		int w, h, numComp;
		unsigned char* data = stbi_load(file.c_str(), &w, &h, &numComp, 4);
		return {data, static_cast<unsigned int>(w), static_cast<unsigned int>(h)};
	}
	void SendData(ImageData id)
	{
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, id.w, id.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, id.data);
	}
private:
	tex_id m_texture;
	std::string m_file;
};

#endif