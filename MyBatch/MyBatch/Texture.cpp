#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Texture.h"

/* Create an array of 10 Texture* */
std::vector<Texture*> Texture::vTextures(10);

Texture::Texture()
	:uiTextureHandle(0)
	,iTexWidth(0)
	,iTexHeight(0)
	{}

Texture::~Texture()
{}

GLvoid Texture::loadTexture(const GLchar *pTextureFilePath)
{
	/* Load the texture file with stbi_load_from_file */
	GLint iChannel = 0;
	FILE *pFile = fopen(pTextureFilePath, "rb");
	const unsigned char *pImageData = stbi_load_from_file(pFile, &iTexWidth, 
		                                                  &iTexHeight, 
														  &iChannel, 0);

	//assert(pImageData);

	/* check the texture picture */
	if (pImageData==NULL)
	{
		fprintf(stderr,"The %s texture picture is null.Please check.\n",
				pTextureFilePath);
		getchar();
		glfwTerminate();
		return ;
	}

	/* Generate the texture id */
	glGenTextures(1, &uiTextureHandle);
	glBindTexture(GL_TEXTURE_2D, uiTextureHandle);

	/* Ensure available the any size texture */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* check the texture id */
	assert(glIsTexture(uiTextureHandle));

	/*if (glIsTexture(m_iTexture)==GL_FALSE)
	{
		fprintf(stderr,"Is not currently the name of texture.Or some 
		      error occurs.Please check.\n");
		getchar();
		glfwTerminate();
		return ;
	}*/

	/* Generate the texture */
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iTexWidth, iTexHeight, 0, GL_RGB,
		         GL_UNSIGNED_BYTE, pImageData);

	/* Release the texture picture buffer */
	free((void *) pImageData);
	pImageData = NULL;

	/* Set the texture parameters */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GLvoid Texture::addManageTexture()
{
	vTextures.push_back(this);
}

GLuint Texture::getTextureID()
{
	return uiTextureHandle;
}

GLuint* Texture::getAddTextureID()
{
	return &uiTextureHandle;
}

GLint Texture::getTexHeight()
{
	return iTexHeight;
}

GLvoid Texture::setTexHeight(GLint iHeight)
{
	iTexHeight = iHeight;
}

GLint Texture::getTexWidth()
{
	return iTexWidth;
}

GLvoid Texture::setTexWidth(GLint iWidth)
{
	iTexWidth = iWidth;
}

GLvoid Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, uiTextureHandle);
}

GLvoid Texture::bind(GLint iUnit)
{
	glActiveTexture(GL_TEXTURE0 + iUnit);
	glBindTexture(GL_TEXTURE_2D, uiTextureHandle);
}

GLboolean Texture::notEqual(const Texture &aTexture)
{
	if ( (aTexture.uiTextureHandle != this->getTextureID()) && 
		 (aTexture.iTexWidth  != this->getTexWidth()) && 
		 (aTexture.iTexHeight != this->getTexHeight()))
	{
		return GL_TRUE;
	}
	else
	{
		return GL_FALSE;
	}
}

GLvoid Texture::deleteTexture()
{
	if (uiTextureHandle != 0)
	{
		glDeleteTextures(1, &uiTextureHandle);
		uiTextureHandle = 0;
	}
}
