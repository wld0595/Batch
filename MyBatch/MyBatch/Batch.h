/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : Batch.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 09:54 
    *  @brief    : 
	*
	*  1.A Batch is used to draw 2D rectangles that reference a texture.
	*    
	*  2.To draw something with a Batch one has to first call the  
	*  {Batch#begin()} method which will setup appropriate render states. When 
	*  you are done with drawing you have to call {Batch#end()} which will 
	*  actually draw the things you specified.
	*
	*  3.All drawing commands of the Batch operate in screen coordinates. The 
	*  screen coordinate system has an x-axis pointing to the right, an y-axis 
	*  pointing upwards and the origin is in the lower left corner of the 
	*  screen.You can also provide your own  transformation and projection  
	*  matrices if you so wish.
	*
	*  4.A Batch is a pretty heavy object so you should only ever have one in 
	*  your program.
	*
	*  5.A Batch works with OpenGL ES 2.0. It will use its own custom shader to
	*  draw all provided sprites. You can set your own custom shader 
	*  via {#setShader(ShaderProgram)}.
	*
	*  6.A Batch has to be disposed if it is no longer used.
*****************************************************************************/ 

#ifndef BATCH_H
#define BATCH_H

#include <gl/glew.h>
#include <GLFW/glfw3.h>

/* class forward declaration:used to solve the repeat head file */
class Texture;
class Shader;
class Batch
{
public:

	/*
	 *  @describe :  New a batch 
	 */ 
	Batch();

	~Batch();

	/*
	 *  @describe :  Set up the Batch for drawing.
	 */ 
	virtual GLvoid begin();

	/*
	 *  @describe :  Finishes off rendering.Must always be called after a call
	 *               to {#begin()}
	 */ 
	virtual GLvoid end();

	/*
	 *  @describe :  draws a rectangle with the bottom left corner at x,y  
	 *               having the given width and height.The rectangle is offset 
	 *               by originX,originY relative to the origin.Scale specifies  
	 *               the scaling factor by which the rectangle should be scaled  
	 *               around originX,originY.Rotation specifies the angle of   
	 *               counter clockwise rotation of the rectangle around originX, 
	 *               originY.The portion of the {Texture} given by srcX,srcY and 
	 *               srcWidth,srcHeight is used.These coordinates and sizes are 
	 *               given in texels.FlipX and FliY specify whether the texture 
	 *               portion should be flipped horizontally or vertically.
	 *  @param    :  const Texture &texture -- the render texture
	 *  @param    :  GLfloat x -- the x coordinate in screen space
	 *  @param    :  GLfloat y -- the y coordinate in screen space
	 *  @param    :  GLfloat originX -- the x coordinate of the scaling and 
	 *                 rotation origin relative to the screen space coordinates
	 *  @param    :  GLfloat originY -- the y coordinate of the scaling and 
	 *                 rotation origin relative to the screen space coordinates
	 *  @param    :  GLfloat width -- the width
	 *  @param    :  GLfloat height -- the height
	 *  @param    :  GLfloat scaleX -- the scale of the rectangle around 
	 *                              originX/originY in x
	 *  @param    :  GLfloat scaleY -- the scale of the rectangle around 
	 *                              originX/originY in y
	 *  @param    :  GLint srcX -- the x coordinate in texel space
	 *  @param    :  GLint srcY -- the y coordinate in texel space
	 *  @param    :  GLint srcWidth -- the source with in texels
	 *  @param    :  GLint srcHeight -- the source height in texels
	 *  @param    :  GLboolean flipX -- whether to flip the sprite horizontally
	 *  @param    :  GLboolean flipY -- whether to flip the sprite vertically
	 */ 
	virtual GLvoid draw(const Texture &texture, GLfloat x, GLfloat y, 
	                    GLfloat originX, GLfloat originY, GLfloat width,
						GLfloat height, GLfloat scaleX, GLfloat scaleY, 
						GLfloat rotation, GLint srcX, GLint srcY, 
						GLint srcWidth, GLint srcHeight,
		                GLboolean flipX, GLboolean flipY);
	/*
	 *  @describe :  Causes any pending sprites to be rendered,without ending
	 *               the Batch.
	 */ 
	virtual GLvoid flush();

	/*
	 *  @describe :  Set the shader to be used.Vertex position attribute is  
	 *               called "a_position",the texture coordinates attribute is 
	 *               called "a_texCoord0",which gets "0" appended to indicate 
	 *               the use of the first texture unit.the color attribute i 
	 *               called "a_color".The combined transform and projection 
	 *               matrix is uploaded via mat4 uniform call "u_projTrans".The  
	 *               texture sampler is passed via a uniform called "u_texture".
	 *               Call this method with a NULL pointer to use the default 
	 *               shader.This method will flush the batch before setting the 
	 *               new shader,you can call it in between {begin()} and {end()}
	 *  @param    :  Shader *shader -- custom shader or null to use the defalut
	 *                                shader
	 */ 
	virtual GLvoid setShader(Shader *shader);

	/*
	 *  @describe :  Return true if currently between begin and end
	 *  @return   :  GLboolean.This is the flag of function call.
	 */ 
	virtual GLboolean isDrawing();

	/*
	 *  @describe :  Release all resources of this object.
	 */ 
	virtual GLvoid dispose();

private:

};

#endif