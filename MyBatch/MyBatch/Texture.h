/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : Texture.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 09:54 
    *  @brief    :   
	*
	*  1.Texture class:used to load texture data.
	*  
	*  2.A Texture has to be bound via the {Texture#bind()} method in order for  
	*  it to be applied to geometry. The texture will be bound to the currently 
	*  texture unit 0 acquiescently.
	*
	*  3.A Texture must be delete when it is no longer used.
*****************************************************************************/ 

#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	
	/*
	 *  @describe :  Set the default value of texture handle,width and height.
	 */ 
	Texture();

	~Texture();

	/*
	 *  @describe :  Load the texture with file path of texture.
	 *  @param    :  const GLchar *pTextureFilePath -- the file path of texture
	 */ 
	GLvoid loadTexture(const GLchar *pTextureFilePath);

	/*
	 *  @describe :  Manage the texture for every new texture.
	 */ 
	GLvoid addManageTexture();

	/*
	 *  @describe :  Get the handle of texture.
	 *  @return   :  GLuint.This is the handle of texture. 
	 */ 
	GLuint getTextureID();

	/*
	 *  @describe :  Get the address of texture handle.
	 *  @return   :  GLuint*.This is the pointer of texture handle. 
	 */ 
	GLuint* getAddTextureID();

	/*
	 *  @describe :  Get the height of the texture.
	 *  @return   :  GLint.This is the height of the texture.
	 */ 
	GLint getTexHeight();

	/*
	 *  @describe :  Set the height of texture 
	 *  @param    :  GLint iHeight -- specified the height of texture
	 */ 
	GLvoid setTexHeight(GLint iHeight);

	/*
	 *  @describe :  Get the width of the texture
	 *  @return   :  GLint.This is the width of texture.
	 */ 
	GLint getTexWidth();

	/*
	 *  @describe :  Set the width of texture
	 *  @param    :  GLint iWidth -- specified the width of texture
	 */ 
	GLvoid setTexWidth(GLint iWidth);

	/*
	 *  @describe :  Binds this texture. The texture will be bound to the  
	 *               texture unit 0. 
	 */ 
	GLvoid bind();

	/*
	 *  @describe :  Binds the texture to the given texture unit.
	 *  @param    :  GLint iUnit -- specified the texture unit.
	 */ 
	GLvoid bind(GLint iUnit);

	/*
	 *  @describe :  Compares two texture objects for reference equality and,
	 *               if they are equal, return false. 
	 *  @param    :  const Texture &aTexture -- specified the compare texture 
	 *               object
	 *  @return   :  GLboolean 
	 */ 
	GLboolean notEqual(const Texture &aTexture);

	/*
	 *  @describe :  Destroys the texture.
	 */ 
	GLvoid deleteTexture();

private:
	/* handle of texture */
	GLuint uiTextureHandle;

	/* width of texture */
	GLint iTexWidth;

	/* height of texture */
	GLint iTexHeight;

	static std::vector<Texture*> vTextures;
};

#endif