#include <stdio.h>
#include <stdlib.h>
#include "FrameBuffer.h"

/* Create an array of 10 FrameBuffer* */
std::vector<FrameBuffer*> FrameBuffer::vFrameBuffer(10);

/* Construct function */
FrameBuffer::FrameBuffer(GLint iWidth, GLint iHeight)
	:uiFboHandle(0)
	,iFboWidth(iWidth)
	,iFboHeight(iHeight)
	,bBuild(GL_FALSE)
{
	build();
	if (isBuild())
	{
		addManagedFrameBuffer();
	}
}

FrameBuffer::~FrameBuffer()
{}

/* Create a frame buffer object */
GLvoid FrameBuffer::build()
{
	glGenTextures(1, tRenderTex.getAddTextureID());
	glBindTexture(GL_TEXTURE_2D, tRenderTex.getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, iFboWidth, iFboHeight, 0,
		         GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenFramebuffers(1, &uiFboHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, uiFboHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
		                   tRenderTex.getTextureID(),0);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("The frame buffer object create failed.Please check now!\n");
		getchar();
		bBuild = GL_FALSE;
		return ;
	}

	/* Set the size of render texture */ 
	tRenderTex.setTexWidth(iFboWidth);
	tRenderTex.setTexHeight(iFboHeight);

	bBuild = GL_TRUE;
}

GLvoid FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, uiFboHandle);
}

GLvoid FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLvoid FrameBuffer::addManagedFrameBuffer()
{
	vFrameBuffer.push_back(this);
}

GLboolean FrameBuffer::isBuild()
{
	return bBuild;
}

GLint FrameBuffer::getFboWidth()
{
	return iFboWidth;
}

GLint FrameBuffer::getFboHeight()
{
	return iFboHeight;
}

GLuint FrameBuffer::getFrameBufferHandle()
{
	return uiFboHandle;
}

Texture FrameBuffer::getRenderTexture()
{
	return tRenderTex;
}

GLvoid FrameBuffer::begin()
{
	bind();
	setFrameBufferViewport();
}

GLvoid FrameBuffer::setFrameBufferViewport()
{
	/* The size of texture */
	glViewport(0, 0, iFboWidth, iFboHeight);
}

GLvoid FrameBuffer::end(GLint iWidth, GLint iHeight)
{
	unbind();
	/* The size of window */
	glViewport(0, 0, iWidth, iHeight);
}

GLvoid FrameBuffer::dispose()
{
	tRenderTex.deleteTexture();
	glDeleteFramebuffers(1, &uiFboHandle);
}



