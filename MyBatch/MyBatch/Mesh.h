/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : Mesh.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 10:53 
    *  @brief    :    
	* 
	*  1.Mesh class:used to creat the vertex and index buffer object,then fill
	*  data,and enable the vertex attribute,draw triangles
	*
	*  2.A Mesh consists of vertex and optionally indices which specify which
	*  vertex define a triangle.Each vertex is composed of attributes such as
	*  position,and texture coordinate.
*****************************************************************************/ 
#ifndef MESH_H
#define MESH_H

#include <assert.h>

#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"

/* Vertex data struct */
typedef struct 
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat u;
	GLfloat v;
}Vertex;

class Mesh
{
public:
	
	/*
	 *  @describe :  Creates a new Mesh.Include create a vertexBufferObject
	 *               and indexBufferObject. 
	 */ 
	Mesh();

	~Mesh();

	/*
	 *  @describe :  Create a new indexBufferObject.
	 */ 
	GLvoid indexBufferObject();

	/*
	 *  @describe :  Create a new vertexBufferObject.
	 */ 
	GLvoid vertexBufferObject();

	/*
	 *  @describe :  Manage the mesh for every new mesh.
	 */ 
	GLvoid addManageMesh();

	/*
	 *  @describe :  Fill the index data to index buffer.
	 *  @param    :  const GLshort *pIndices -- the indices array
	 *  @param    :  GLint iNumber -- the iNumber of the indices array
	 */ 
	GLvoid fillIndexData(const GLshort *pIndices, GLint iNumber);

	/*
	 *  @describe :  Fill the vertex data to vertex buffer.
	 *  @param    :  const Vertex *pVertex -- the vertex array
	 *  @param    :  GLint iNumber --  the number of the vertex array 
	 */ 
	GLvoid fillVertexData(const Vertex *pVertex, GLint iNumber);

	/*
	 *  @describe :  Get the handle of vertexBufferObject.
	 *  @return   :  GLuint.This is the vertexBufferObject handle.
	 */ 
	GLuint getVertexBuffer();

	/*
	 *  @describe :  Get the handle of vertex array object.
	 *  @return   :  GLuint.This is the vertex array object handle.
	 */ 
	GLuint getVertexArrayID();

	/*
	 *  @describe :  Get the handle of indexBufferObject.
	 *  @return   :  GLuint.This is the indexBufferObject handle. 
	 */ 
	GLuint getIndexID();

	/*
	 *  @describe :  Binds the vertexBufferObject for rendering via 
	 *               glDrawArrays or glDrawElements
	 *  @param    :  Shader *pShader -- current shader  
	 */ 
	GLvoid bind(Shader *pShader);

	/*
	 *  @describe :  Unbinds the VertexBufferObject.
	 *  @param    :  Shader *pShader -- current shader
	 */ 
	GLvoid unbind(Shader *pShader);

	/*
	 *  @describe :  Render the mesh.
	 *               This method will automatically bind each vertex attribute  
	 *               as specified at construction time to the respective shader
	 *               attributes.The binding is based on the alias defined for 
	 *               each VertexAttribute.This method must only be called after 
	 *               the {Shader#begin()} method has been called!
	 *  @param    :  Shader *pShader -- the current shader
	 *  @param    :  GLint iCount -- the number of sprite batch
	 */ 
	GLvoid render(Shader *pShader, GLint iCount);

	/*
	 *  @describe :  Delete the IndexBufferObject,VertexAarrayObject
	 *               and VertexBufferObject 
	 */ 
	GLvoid dispose();

private:
	/* indexBufferObject handle */
	GLuint uiIndexBuffer;

	/* VertexArrayObjcet handle */
	GLuint uiVertexArrayID;

	/* vertexBufferObject handle */
	GLuint uiVertexBuffer;	

	static std::vector<Mesh*> vMesh;
};

#endif