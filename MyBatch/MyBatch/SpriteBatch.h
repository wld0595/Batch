/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : SpriteBatch.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 13:54 
    *  @brief    :    
	*
	*  1.According the position,width and height ... to draw texture
	*
	*  2.Draws batched quads using indices.
*****************************************************************************/ 
#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Batch.h"
#include "Mesh.h"
#include "Texture.h"

//=======================//
class SpriteBatch:public Batch
{
public:

	/*
	 *  @describe :  Constructs a new SpriteBatch.Sets the projection matrix to 
	 *               an orthographic projection with y-axis point upwards, 
	 *               x-axis point to the right and the origin being in the 
	 *               bottom left corner of the screen.
	 */ 
	SpriteBatch();

	/*
	 *  @describe :  Release memory of the indices and vertex array. 
	 */ 
	~SpriteBatch();

	/*
	 *  @describe :  Create a default shader 
	 *  @return   :  Shader*.This is a new instance of the default shader.
	 */ 
	Shader* createDefaultShader();

	/*
	 *  @describe :  Set up the SpriteBatch for drawing.
	 */ 
	GLvoid begin();

	/*
	 *  @describe :  Finishes off rendering.Must always be called after a call 
	 *               to {#begin()}
	 */ 
	GLvoid end();

	/*
	 *  @describe :  Set up the MVP matrix and deliver to shader,then set the 
	 *               texture unit
	 */ 
	GLvoid setupMatrices();
	
	/*
	 *  @describe :  draws a rectangle with the bottom left corner at x,y having 
	 *               the given width and height.The rectangle is offset by  
	 *               originX,originY relative to the origin.Scale specifies the  
	 *               scaling factor by which the rectangle should be scaled   
	 *               around originX,originY.Rotation specifies the angle of   
	 *               counter clockwise rotation of the rectangle around originX, 
	 *               originY.The portion of the {Texture} given by srcX,srcY and 
	 *               srcWidth,srcHeight is used.These coordinates and sizes are 
	 *	             given in texels.FlipX and FliY specify whether the texture  
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
	 *                                    originX/originY in x
	 *  @param    :  GLfloat scaleY -- the scale of the rectangle around 
	 *                                    originX/originY in y
	 *  @param    :  GLfloat rotation -- the angle of counter clockwise rotation
	 *                                of the rectangle around originX/originY
	 *  @param    :  GLint srcX -- the x coordinate in texel space
	 *  @param    :  GLint srcY -- the y coordinate in texel space
	 *  @param    :  GLint srcWidth -- the source with in texels
     *  @param    :  GLint srcHeight -- the source height in texels
	 *  @param    :  GLboolean flipX -- whether to flip the sprite horizontally
	 *  @param    :  GLboolean flipY -- whether to flip the sprite vertically
	 */ 
	GLvoid draw(const Texture &texture, GLfloat x, GLfloat y, GLfloat originX,
		        GLfloat originY, GLfloat width, GLfloat height, 
		        GLfloat scaleX, GLfloat scaleY, GLfloat rotation, GLint srcX,  
		        GLint srcY, GLint srcWidth, GLint srcHeight,
				GLboolean flipX, GLboolean flipY);

	/*
	 *  @describe :  Flush the last texture,and switch texture to the last 
	 *               texture.
	 *  @param    :  const Texture &texture -- the current texture
	 */ 
	GLvoid switchTexture(const Texture &texture);

	/*
	 *  @describe :  Causes any pending sprites to be rendered,without ending 
	 *               the SpriteBatch.
	 */ 
	GLvoid flush();

	//************************************
	// Describe:  Set the shader to be used.Vertex position attribute is called 
	//            "a_position",the texture coordinates attribute is called 
	//            "a_texCoord0",which gets "0" appended to indicate the use of 
	//            the first texture unit.the color attribute i called "a_color".
    //	          The combined transform and projection matrix is uploaded via
	//            mat4 uniform call "u_projTrans".The texture sampler is passed 
	//            via a uniform called "u_texture".Call this method with a NULL 
	//            pointer to use the default shader.This method will flush the 
    //            sprite-batch before setting the new shader,you can call it in 
	//            between {begin()} and {end()}
	// Method:    setShader
	// FullName:  SpriteBatch::setShader
	// Access:    public 
	// Returns:   GLvoid
	// Parameter: Shader *pShader -- custom shader or null to use the defalut 
	//                           shader
	//************************************
	/*
	 *  @describe :  Set the shader to be used.Vertex position attribute is  
	 *               called "a_position",the texture coordinates attribute is 
	 *               called "a_texCoord0",which gets "0" appended to indicate 
	 *               the use of the first texture unit.the color attribute i 
	 *	             called "a_color".The combined transform and projection 
	 *               matrix is uploaded via mat4 uniform call "u_projTrans".The  
	 *               texture sampler is passed via a uniform called "u_texture". 
	 *               Call this method with a NULL pointer to use the default 
	 *               shader.This method will flush the sprite-batch before  
	 *               setting the new shader,you can call it in between {begin()}
     *	             and {end()}
	 *  @param    :  Shader *pShader -- custom shader or null to use the defalut
	 *                                shader 
	 */ 
	GLvoid setShader(Shader *pShader);

	/*
	 *  @describe :  Get the current shader or th edefaultShader 
	 */ 
	Shader* getShader();

	/*
	 *  @describe :  Return true if currently between begin and end
	 *  @return   :  GLboolean
	 */ 
	GLboolean isDrawing();

	/*
	 *  @describe :  Set up the projection matrix by orthographic
	 *  @param    :  GLfloat fLeft -- projection of the left (x) border
	 *  @param    :  GLfloat fRight -- projection of the right (-x) border
	 *  @param    :  GLfloat fBottom -- projection of the bottom (-y) border
	 *  @param    :  GLfloat fUp -- projection of the up (y) border
	 *  @param    :  GLfloat fNear -- projection of the near (z) border
	 *  @param    :  GLfloat fFar -- projection of the far (-z) border 
	 */ 
	GLvoid setProjectionMatrix(GLfloat fLeft, GLfloat fRight, GLfloat fBottom, 
		                       GLfloat fUp, GLfloat fNear, GLfloat fFar);

	/*
	 *  @describe :  Releases all resources of this object.
	 *               Include the mesh,shader and texture. 
	 */ 
	GLvoid dispose();

private:
	/* The max number of sprites in a single batch. */
	GLint miSize;

	/* The flag of call begin() */
	GLboolean mbDrawing;

	/* The pointer of vertex array */
	Vertex *mpVertices;

	/* The pointer of index array */
	GLshort *mpIndices;

	/* Statistics the number of render */
	GLint miRenderCalls;
	GLint miTotalRenderCalls;

	/* The number of vertex  */
	GLint miCount;

	/* Inverse width and height of texture */
	GLfloat mfInvTexWidth;
	GLfloat mfInvTexHeight;

	/* The texture object */
	Texture mLastTexture;

	/* The shader object */
	Shader *mDefaultShader;
	Shader *mCustomShader;

	/* The mesh object */
	Mesh mMesh;

	/* Index value of "u_projTrans" */
	GLint miMatrixID;

	/* Index value of "u_texture" */
	GLint miTextureID;

	/* Orthogonality projection matrix */ 
	glm::mat4 mProjectionMatrix;
	glm::mat4 mModelMatrix;

	/* Mix matrix (mProjectionMatrix*mModelMatrix) */
	glm::mat4 mMVP;

	/* The maximum number of sprites rendered in one batch so far */
	GLint miMaxSpritesInBatch;
};

#endif