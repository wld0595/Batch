/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : FrameBuffer.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 10:40 
    *  @brief    : Used to create a frame buffer object 
*****************************************************************************/ 
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "Texture.h"

class FrameBuffer
{
public:

	/*
	 *  @describe :  Create a new FrameBuffer having the given width and height.
	 *  @param    :  GLint iWidth -- the width of FrameBuffer
	 *  @param    :  GLint iHeight -- the height of FrameBuffer
	 */ 
	FrameBuffer(GLint iWidth,GLint iHeight);

	~FrameBuffer();

	/*
	 *  @describe :  Build a FrameBuffer
	 *  @return   :  GLvoid
	 */ 
	GLvoid build();

	/*
	 *  @describe :  Make the frame buffer current so everything gets drawn 
	 *               to it.
	 *  @return   :  GLvoid
	 */ 
	GLvoid bind();

	/*
	 *  @describe : Unbind the frame buffer,all drawing will be performed to  
	 *              the normal frame buffer from here on.
	 *  @return   : GLvoid
	 */ 
	GLvoid unbind();

	/*
	 *  @describe :  Add every new frame buffer to a vector.
	 *  @return   :  GLvoid
	 */ 
	GLvoid addManagedFrameBuffer();

	/*
	 *  @describe :  Whether build the frame buffer success.
	 *  @return   :   GLboolean.The flag of frame buffer.
	 */ 
	GLboolean isBuild();

	/*
	 *  @describe :  Get the width of frame buffer.
	 *  @return   :   GLint.This is the width of frame buffer.
	 */ 
	GLint getFboWidth();

	/*
	 *  @describe :  Get the height of frame buffer.
	 *  @return   :  GLint.This is the height of frame buffer.
	 */ 
	GLint getFboHeight();

	/*
	 *  @describe :  Get the handle of the frame buffer.
	 *  @return   :  GLuint.This is the handle of frame buffer.
	 */ 
	GLuint getFrameBufferHandle();

	/*
	 *  @describe :  Get the texture object.
	 *  @return   :  Texture.The texture object.
	 */ 
	Texture getRenderTexture();

	/*
	 *  @describe :  Bind the frame buffer and sets the view-port accordingly,
	 *               so everything gets drawn to it
	 */ 
	GLvoid begin();

	/*
	 *  @describe :  Set view-port to the dimensions of framebuffer.Called by
	 *               {#begin()}
	 */ 
	GLvoid setFrameBufferViewport();

	/*
	 *  @describe :  Unbind the frame buffer,all drawing will be performed to  
	 *               the normal frame buffer from here on.
	 *  @param    :  GLint iWidth -- the width of window
	 *  @param    :  GLint iHeight -- the height of window
	 */ 
	GLvoid end(GLint iWidth, GLint iHeight);

	/*
	 *  @describe :  Release all resources associated with the frame buffer
	 *               Include the texture and FrameBufferObject.
	 */ 
	GLvoid dispose();

private:
	/* The frame buffer object handle */
	GLuint uiFboHandle;

	/* The frame buffer width and height */
	GLint iFboWidth;
	GLint iFboHeight;

	/* The render texture object */
	Texture tRenderTex;

	/* The flag of build */
	GLboolean bBuild;

	/* manage the frame buffer */
	static std::vector<FrameBuffer*> vFrameBuffer;
};

#endif