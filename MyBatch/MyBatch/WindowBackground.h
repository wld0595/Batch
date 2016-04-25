/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : WindowBackground.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 13:52 
    *  @brief    :    
	*
	*  1.Used to create the environment of running OpenGL
*****************************************************************************/ 
#ifndef WINDOWBACKGROUND_H
#define WINDOWBACKGROUND_H

#include <stdio.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class WindowBackground
{
public:

	/*
	 *  @describe :  Create a default window.The size is 960*512. 
	 */ 
	WindowBackground();

	/*
	 *  @describe :  Create a window as specified the size.
	 *  @param    :  GLFWwindow *pWindow -- the handle of window 
	 *  @param    :  GLint iWidth -- the width of window
	 *  @param    :  GLint iHeight -- the height of window
	 *  @param    :  GLchar *pTitle -- the title of window
	 */ 
	WindowBackground(GLFWwindow *pWindow, GLint iWidth, GLint iHeight, 
		             GLchar *pTitle);

	/*
	 *  @describe :  Release the handle of window and the pointer of title.
	 */ 
	~WindowBackground();

	/*
	 *  @describe :  Reset the size of window. 
	 *  @param    :  GLFWwindow *pWindow -- the handle of window
	 *  @param    :  GLint iWidth -- the width of window
	 *  @param    :  GLint iHeight -- the height of window
	 *  @param    :  GLchar *pTitle -- the title of window 
	 */ 
	GLvoid setWindow(GLFWwindow *pWindow, GLint iWidth, GLint iHeight,
		             GLchar *pTitle);

	/*
	 *  @describe :  Create a environment of running OpenGL.Include initialized 
	 *               the GLFW,set some hints,create window,make the context,
	 *               initialized the GLEW and set the input mode.
	 */ 
	GLvoid initi();

	/*
	 *  @describe :  Get the width of window.
	 *  @return   :  GLint.This is the width of window.
	 */ 
	GLint getWindowWidth();

	/*
	 *  @describe :  Get the height of window.
	 *  @return   :  GLint.This is the height of window. 
	 */ 
	GLint getWindowHeight();
	
	/*
	 *  @describe :  Get the handle of window.
	 *  @return   :  GLFWwindow*.This is the handle of window.
	 */ 
	GLFWwindow* getWindowHandle();

	//************************************
	// Describe:  Ensure the AspectRatio of graphic object
	// Method:    changeWindowSize
	// FullName:  WindowBackground::changeWindowSize
	// Access:    public 
	// Returns:   GLvoid
	//************************************
	/*
	 *  @describe :  Ensure the AspectRatio of graphic object
	 */ 
	GLvoid changeWindowSize();

protected:
	/* handle of window */
	GLFWwindow *pWindowHandle;

	/* width and height of window */
	GLint iWindowWidth;
	GLint iWindowHeight;

	/* title of window */
	GLchar *pWindowTitle;
};

#endif













