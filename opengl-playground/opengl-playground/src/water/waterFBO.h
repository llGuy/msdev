#ifndef WATER_FBO_HEADER
#define WATER_FBO_HEADER

#include <GL/glew.h>

class WaterFrameBuffer
{
public:
	explicit WaterFrameBuffer(void)
	{
		m_reflectionFrameBuffer = CreateFrameBuffer();
		m_reflectionTexture = CreateTextureAttachment(320, 180);
		m_reflectionDepthBuffer = CreateDepthBufferAttachment(320, 180);

		m_refractionFrameBuffer = CreateFrameBuffer();
		m_refractionTexture = CreateTextureAttachment(1280, 720);
		m_refractionDepthTexture = CreateDepthTextureAttachment(1280, 720);
		UnbindFramebuffer();
	}

private:
	void BindFrameBuffer(int frameBuffer, int width, int height)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glViewport(0, 0, width, height);
	}
	void UnbindFramebuffer(void)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	unsigned int CreateFrameBuffer(void)
	{
		unsigned int fb;
		glGenFramebuffers(1, &fb);
		glBindFramebuffer(GL_FRAMEBUFFER, fb);
		// which color buffer attachment in the currently bound FBO
		// we want to render to (you can add multiple and select which one you want to draw to)
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		return fb;
	}
	unsigned int CreateTextureAttachment(int width, int height)
	{
		// attach the color buffer texture
		unsigned int t;
		glGenTextures(1, &t);
		glBindTexture(GL_TEXTURE_2D, t);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, t, 0);
		return t;
	}
	unsigned int CreateDepthTextureAttachment(int width, int height)
	{
		// attach the depth buffer texture
		unsigned int d;
		glGenTextures(1, &d);
		glBindTexture(GL_TEXTURE_2D, d);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, d, 0);
		return d;
	}
	unsigned int CreateDepthBufferAttachment(int width, int height)
	{
		unsigned int d;
		glGenRenderbuffers(1, &d);
		glBindRenderbuffer(GL_RENDERBUFFER, d);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, d);
		return d;
	}
private:
	unsigned int m_refractionFrameBuffer;
	unsigned int m_refractionTexture;
	unsigned int m_refractionDepthTexture;

	unsigned int m_reflectionFrameBuffer;
	unsigned int m_reflectionTexture;
	unsigned int m_reflectionDepthBuffer;
};

#endif