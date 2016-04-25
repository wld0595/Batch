/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : ShaderProgram.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 11:05 
    *  @brief    :  
	*  
	*  1.A shader program encapsulates a vertex and fragment shader pair linked 
	*  to form a shader program.
	*
	*  2.To make the GPU use a specific ShaderProgram the programs 
	*  {Shader#begin()} method must be used which effectively binds the program.
	*
	*  3.When a ShaderProgram is bound one can set uniforms, vertex attributes 
	*  and attributes as needed via the respective methods
	*
	*  4.A ShaderProgram can be unbound with a call to {Shader#end()}
	*
	*  5.A ShaderProgram must be disposed via a call to {Shader#dispose()} when 
	*  it is no longer needed
*****************************************************************************/ 
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <assert.h>

#include <map>
#include <string>
#include <vector>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
public:

	/*
	 *  @describe :  Construct a new shader program by string and immediately
	 *               compiles it.
	 *  @param    :  const std::string sVertexShader -- vertex shader source 
	 *                                                 code
	 *  @param    :  const std::string sFragmentShader -- fragment shader  
	 *                                                source code 
	 */ 
	Shader(const std::string sVertexShader, const std::string sFragmentShader);

	/*
	 *  @describe :  Construct a new shader program by file and immediately 
	 *               compiles it.
	 *  @param    :  const GLchar *pVertexFilePath -- vertex shader file path
	 *  @param    :  const GLchar *pFragmentFilePath -- fragment shader 
	 *                                                file path
	 */ 
	Shader(const GLchar *pVertexFilePath, const GLchar *pFragmentFilePath);

	~Shader();

	/*
	 *  @describe :  Check the current shader is valid.
	 */ 
	GLvoid checkManaged();

	/*
	 *  @describe :  Loads and compiles the shader,creates a new program by  
	 *               default shader source code and link the shader
	 */ 
	GLvoid compileShaders();

	/*
	 *  @describe :  Loads and compiles the shader,creates a new program by  
	 *               file and link the shader.
	 *  @param    :  const GLchar *pVertexFilePath --  vertex shader file path
	 *  @param    :  const GLchar *pFragmentFilePath -- fragment shader 
	 *                                            file path
	 */ 
	GLvoid compileShaders(const GLchar *pVertexFilePath, 
		                  const GLchar *pFragmentFilePath);
	
	/*
	 *  @describe :  Load the vertex or fragment shader by file.
	 *  @param    :  GLint iType -- GL_VERTEX_SHADER (vertex shader) or
	 *                            GL_FRAGMENT_SHADER (fragment shader)
	 *  @param    :  const GLchar *pFilePath -- the vertex shader or 
	 *                            fragment shader file path
	 *  @return   :  GLint.This is the handle of vertex shader handle or  
	 *               fragment shader 
	 */ 
	GLint loadShader(GLint iType, const GLchar *pFilePath);

	/*
	 *  @describe :  Link the shader.
	 */ 
	GLvoid linkProgram();

	/*
	 *  @describe :  Print the log info for the shader compilation and program
	 *               linking stage.
	 *  @param    :  GLint iType -- GL_VERTEX_SHADER (vertex shader) or 
	 *                            GL_FRAGMENT_SHADER (fragment shader)
	 *  @return   :  GLint.Whether is error when compile. 
	 */ 
	GLint getLog(GLint iType);

	/*
	 *  @describe :  Activate shader program
	 */ 
	GLvoid begin();

	/*
	 *  @describe :  Activate the shader program 0
	 */ 
	GLvoid end();

	/*
	 *  @describe :  Get the handle of shader program.
	 *  @return   :  GLuint.This is the handle of shader program
	 */ 
	GLuint getProgramID();

	/*
	 *  @describe :  Get all the location and name of uniform.
	 */ 
	GLvoid fetchUniforms();

	/*
	 *  @describe :  Get all the location and name of attribute. 
	 */ 
	GLvoid fetchAttributes();

	/*
	 *  @describe :  Get the location of uniform by name.
	 *  @param    :  const GLchar *pName --  the uniform name
	 *  @return   :  GLint.This is the uniform location. 
	 */ 
	GLint fetchUniformLocation(const GLchar *pName);

	/*
	 *  @describe :  Get the location of attribute by name
	 *  @param    :  const GLchar *pName --  the attribute name
	 *  @return   :  GLint.This is the attribute location.
	 */ 
	GLint fetchAttributeLocation(const GLchar *pName);

	/*
	 *  @describe :  Manage the shader for every new shader.
	 */ 
	GLvoid addManagedShader();

	/*
	 *  @describe :  Get the flag of compilation.
	 *  @return   :  GLboolean.When the shader compilation success,return true. 
	 */ 
	GLboolean isCompiled();

	/*
	 *  @describe :  Get the number of attribute. 
	 *  @return   :  GLint.This is the number of attribute. 
	 */ 
	GLint getAttributeSize();

	/*
	 *  @describe :  Get the number of uniform.
	 *  @return   :  GLint.This is the number of uniform.
	 */ 
	GLint getUniformSize();

	/*
	 *  @describe :  Enables the vertex attribute with the given location.
	 *  @param    :  GLint iLocation -- the specified location of attribute
	 */ 
	GLvoid enableVertexAttribute(GLint iLocation);

	/*
	 *  @describe :  Disables the vertex attribute with the given location.
	 *  @return   :  GLint iLocation -- the specified location of attribute
	 */ 
	GLvoid disableVertexAttribute(GLint iLocation);

	/*
	 *  @describe :  Get the name of the attribute by location.
	 *  @param    :  GLint iLocation -- the specified location of attribute.
	 *  @return   :  std::string.This is the attribute name.
	 */ 
	std::string getAttributeName(GLint iLocation);

	/*
	 *  @describe :  Get the name of the uniform by location.
	 *  @param    :  GLint iLocation -- the specified location of uniform.
	 *  @return   :  std::string.This is the uniform name.
	 */ 
	std::string getUniformName(GLint iLocation);

	/*
	 *  @describe :  Set the uniform value with the given name.
	 *  @param    :  const std::string sName -- the name of uniform
	 *  @param    :  GLfloat fValue -- the value 
	 */ 
	GLvoid setUniformf(const std::string sName, GLfloat fValue);

	/*
	 *  @describe :  Set the vertex attribute with the given location.
	 *  @param    :  GLint iLocation -- the attribute location
	 *  @param    :  GLint iSize -- the number of components,must be >=1 and 
	 *                            <= 4
	 *  @param    :  GLint iType -- must be one of GL20.GL_BYTE,  
	 *               GL20.GL_UNSIGNED_BYTE,GL20.GL_SHORT,GL20.GL_UNSIGNED_SHORT,
	 *               GL20.GL_FIXED, or GL20.GL_FLOAT. GL_FIXED will not work on 
	 *               the desktop
	 *  @param    :  GLboolean bNormalize -- whether fixed point data should be
	 *                                    normalized
	 *  @param    :  GLint iStride -- the stride in bytes between successive
	 *                                    attributes
	 *  @param    :  const GLvoid * pPointer -- the buffer containing the 
	 *                                     vertex attributes
	 */ 
	GLvoid setVertexAttribute(GLint iLocation, GLint iSize, GLint iType, 
		                      GLboolean bNormalize, GLint iStride, 
							  const GLvoid *pPointer);

	/*
	 *  @describe :  Delete the handle of vertex and fragment shader.
	 */ 
	GLvoid deleteShader();

	/*
	 *  @describe :  Delete the shader program.
	 */ 
	GLvoid dispose();
	
private:
	/* Shader program handle */
	GLuint uiProgramID;

	/* whether this shader was invalidated */
	GLboolean bInvalidated;

	/* File path of the vertex and fragment shade */
	const GLchar *pVertexShaderFile;
	const GLchar *pFragmentShaderFile;

	/* vertex and fragment handle */
	GLint iVertexShaderHandle;
	GLint iFragmentShaderHandle;

	/* vertex and fragment shader source code */
	std::string sVertexShaderCode;
	std::string sFragmentShaderCode;

	/* size,name and location of uniform */
	GLint iUniformSize;
	std::string *pUniformNames;
	GLint *pUniformLocation;
	std::map<std::string,GLint> mapUniform;

	/* size,name and location of attribute */
	GLint iAttributeSize;
	std::string *pAttributeNames;
	GLint *pAttributeLocation;
	std::map<std::string, GLint> mapAttribute;

	/* whether this shader program compiled successfully */
	GLboolean bCompiled;

	/* manage the shader */
	/* Set static variable used to store all object */
	static std::vector<Shader*>  vShaders;
};

#endif



