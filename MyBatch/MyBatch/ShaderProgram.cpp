#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "ShaderProgram.h"

/* Create an array of 10 Shader* */
std::vector<Shader*> Shader::vShaders(10);

/* Construction function:initialized the member variable */
Shader::Shader(const std::string sVertexShader, 
               const std::string sFragmentShader)
	:uiProgramID(0)
	,bInvalidated(GL_FALSE)
	,pVertexShaderFile(NULL)
	,pFragmentShaderFile(NULL)
	,iVertexShaderHandle(-1)
	,iFragmentShaderHandle(-1)
	,sVertexShaderCode(sVertexShader)
	,sFragmentShaderCode(sFragmentShader)
	,iUniformSize(0)
	,pUniformNames(NULL)
	,pUniformLocation(NULL)
	,iAttributeSize(0)
	,pAttributeNames(NULL)
	,pAttributeLocation(NULL)
	,bCompiled(GL_FALSE)
{
	/* Compile the shader (Include the load shader source code,compile,printf 
	log and link) */
	compileShaders();

	/* If compile success,get location of all attributes and uniforms */
	if (isCompiled())
	{
		fetchAttributes();
		fetchUniforms();
		addManagedShader();
	}
}

/* Construction function:initialized the member variable with some parameter */
Shader::Shader(const GLchar *pVertexFilePath, const GLchar *pFragmentFilePath)
	:uiProgramID(0)
	,bInvalidated(GL_FALSE)
	,pVertexShaderFile(pVertexFilePath)
	,pFragmentShaderFile(pFragmentFilePath)
	,iVertexShaderHandle(-1)
	,iFragmentShaderHandle(-1)
	,sVertexShaderCode("\0")
	,sFragmentShaderCode("\0")
	,iUniformSize(0)
	,pUniformNames(NULL)
	,pUniformLocation(NULL)
	,iAttributeSize(0)
	,pAttributeNames(NULL)
	,pAttributeLocation(NULL)
	,bCompiled(GL_FALSE)
{
	/* Compile the shader (Include the load shader source code,compile,
	printf log and link) */
	compileShaders(pVertexShaderFile, pFragmentShaderFile);

	/* If compile success,get location of all attributes and uniforms */
	if (isCompiled())
	{
		fetchAttributes();
		fetchUniforms();
		addManagedShader();
	}
}

Shader::~Shader()
{}

GLvoid Shader::checkManaged()
{
	if (bInvalidated)
	{
		compileShaders(pVertexShaderFile, pFragmentShaderFile);
		bInvalidated=GL_FALSE;
	}
}

/* Load and compile the shader,create a new program and link the shader */
GLvoid Shader::compileShaders()
{
	/* Create a vertex shader */
	iVertexShaderHandle = glCreateShader(GL_VERTEX_SHADER);
	assert(iVertexShaderHandle != -1);

	/* Create a fragment shader */
	iFragmentShaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
	if (iFragmentShaderHandle == -1)
	{
		glDeleteShader(iVertexShaderHandle);
		bCompiled = GL_FALSE;
		return ;
	}

	char const* vertexSourcePointer = sVertexShaderCode.c_str();
	glShaderSource(iVertexShaderHandle, 1, &vertexSourcePointer, NULL);
	glCompileShader(iVertexShaderHandle);

	GLint errorVertex = getLog(iVertexShaderHandle);

	char const* fragmentSourcePointer = sFragmentShaderCode.c_str();
	glShaderSource(iFragmentShaderHandle, 1, &fragmentSourcePointer, NULL);
	glCompileShader(iFragmentShaderHandle);
	GLint errorFragment = getLog(iFragmentShaderHandle);

	if (errorFragment > 1)
	{
		bCompiled = GL_FALSE;
		deleteShader();
		return ;
	}

	linkProgram();

	bCompiled = (uiProgramID != -1);
}

GLvoid Shader::compileShaders(const GLchar *pVertexFilePath, 
	const GLchar *pFragmentFilePath)
{
	iVertexShaderHandle = loadShader(GL_VERTEX_SHADER, pVertexFilePath);
	assert(iVertexShaderHandle != -1);

	iFragmentShaderHandle = loadShader(GL_FRAGMENT_SHADER, pFragmentFilePath);
	if (iFragmentShaderHandle == -1)
	{
		glDeleteShader(iVertexShaderHandle);
		bCompiled = GL_FALSE;
		return ;
	}

	/*if (iVertexShaderHandle ==-1 || iFragmentShaderHandle==-1)
	{
		bCompiled=GL_FALSE;
		return ;
	}*/

	char const* vertexSourcePointer = sVertexShaderCode.c_str();
	glShaderSource(iVertexShaderHandle, 1, &vertexSourcePointer, NULL);
	glCompileShader(iVertexShaderHandle);

	GLint errorVertex = getLog(iVertexShaderHandle);

	char const* fragmentSourcePointer = sFragmentShaderCode.c_str();
	glShaderSource(iFragmentShaderHandle, 1, &fragmentSourcePointer, NULL);
	glCompileShader(iFragmentShaderHandle);
	GLint errorFragment = getLog(iFragmentShaderHandle);

	if ( (errorVertex > 1) || (errorFragment > 1) )
	{
		bCompiled = GL_FALSE;
		deleteShader();
		return ;
	}

	linkProgram();

	bCompiled = (uiProgramID != -1);

	/*if(uiProgramID==-1)
	{
		bCompiled=GL_FALSE;
		return ;
	}

	bCompiled=GL_TRUE;*/
}

GLint Shader::loadShader(GLint iType, const GLchar *file_path)
{
	GLuint shaderID = glCreateShader(iType);
	std::ifstream shaderStream(file_path, std::ios::in);
	std::string shaderCode = "\0";
	if (shaderStream.is_open())
	{
		std::string sLine = "\0";
		while(getline(shaderStream, sLine))
		{
			shaderCode += "\n" + sLine;
		}
		shaderStream.close();
		if (iType == GL_VERTEX_SHADER)
		{
			sVertexShaderCode = shaderCode;
		}
		else if(iType == GL_FRAGMENT_SHADER)
		{
			sFragmentShaderCode = shaderCode;
		}
		return shaderID;
	}
	else
	{
		printf("Failed to open %s. Are you in the right directory ? \n",
     		file_path);
		getchar();
		return -1;
	}
}

/* Create a new program and links the shader */
GLvoid Shader::linkProgram()
{
	uiProgramID = glCreateProgram();
	glAttachShader(uiProgramID, iVertexShaderHandle);
	glAttachShader(uiProgramID, iFragmentShaderHandle);
	glLinkProgram(uiProgramID);

	GLint errorProgram = getLog(uiProgramID);
	if (errorProgram > 0)
	{
		uiProgramID = -1;
		deleteShader();
		return ;
	}

	glDetachShader(uiProgramID, iVertexShaderHandle);
	glDetachShader(uiProgramID, iFragmentShaderHandle);

	deleteShader();
}

GLint Shader::getLog(GLint iType)
{
	GLint iResult        = GL_FALSE;
	GLint iInfoLogLength = 0;

	glGetShaderiv(iType, GL_COMPILE_STATUS, &iResult);
	glGetShaderiv(iType, GL_INFO_LOG_LENGTH, &iInfoLogLength);
	if (iInfoLogLength > 0)
	{
		std::vector<char> ShaderErrorMessage(iInfoLogLength + 1);
		glGetShaderInfoLog(iType, iInfoLogLength, NULL,
                		   &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}
	return iInfoLogLength;
}

GLvoid Shader::begin()
{
	checkManaged();
	glUseProgram(uiProgramID);
}

GLvoid Shader::end()
{
	glUseProgram(0);
}

GLuint Shader::getProgramID()
{
	return uiProgramID;
}

GLvoid Shader::fetchUniforms()
{
	GLint   iParams    = 0;
	GLsizei iMaxLength = 0;
	GLint   iSize      = 0;
	GLint   iWritten   = 0;
	GLenum  eType      = 0;
	GLchar* cpName     = NULL;
	//GLint   iLocation  = 0;

	glGetProgramiv(uiProgramID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &iMaxLength);
	glGetProgramiv(uiProgramID, GL_ACTIVE_UNIFORMS, &iParams);
	iUniformSize = iParams;
	cpName = new GLchar[iMaxLength];
	pUniformNames = new std::string[iParams];
	pUniformLocation = new GLint[iParams];
	for (GLint i = 0; i < iParams; ++i)
	{
		glGetActiveUniform(uiProgramID, i, iMaxLength, &iWritten, &iSize,
			&eType, cpName);
		pUniformLocation[i] = glGetUniformLocation(uiProgramID, cpName);
		pUniformNames[i] = cpName;
		mapUniform[pUniformNames[i]] = pUniformLocation[i];
		/*iLocation = glGetUniformLocation(uiProgramID, cpName);
		mapUniform[iLocation] = cpName;*/
	}
}

GLvoid Shader::fetchAttributes()
{
	GLint   iParams    = 0;
	GLsizei iMaxLength = 0;
	GLint   iSize      = 0;
	GLint   iWritten   = 0;
	GLenum  eType      = 0;
	GLchar* cpName     = NULL;
	//GLint   iLocation  = 0;

	glGetProgramiv(uiProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &iMaxLength);
	glGetProgramiv(uiProgramID, GL_ACTIVE_ATTRIBUTES, &iParams);
	iAttributeSize = iParams;
	cpName = new GLchar[iMaxLength];
	pAttributeNames = new std::string[iParams];
	pAttributeLocation = new GLint[iParams];
	for(GLint i = 0; i < iParams; ++i)
	{
		glGetActiveAttrib(uiProgramID, i, iMaxLength, &iWritten, &iSize,
			&eType, cpName);
		pAttributeLocation[i] = glGetAttribLocation(uiProgramID, cpName);
		pAttributeNames[i] = cpName;
		mapAttribute[pAttributeNames[i]] = pAttributeLocation[i];
		/*iLocation = glGetAttribLocation(uiProgramID, cpName);
		mapAttribute [iLocation] = cpName;*/
	}
}

GLint Shader::fetchUniformLocation(const GLchar *pName)
{
	GLint iLocation = -1;
	iLocation = mapUniform[pName];
	//location=glGetUniformLocation(uiProgramID,pName);
	//assert(iLocation != -1);
	if (iLocation==-1)
	{
		printf("No exit %s.Please check.",pName);
		getchar();
		exit(1);
	}
	return iLocation;
}

GLint Shader::fetchAttributeLocation(const GLchar *pName)
{
	GLint iLocation = -1;
	iLocation = mapAttribute[pName];
	//location=glGetAttribLocation(uiProgramID,pName);
	//assert(iLocation != -1);
	if (iLocation==-1)
	{
		printf("No exit %s.Please check.",pName);
		getchar();
		exit(1);
	}
	return iLocation;
}

GLvoid Shader::addManagedShader()
{
	vShaders.push_back(this);
}

GLboolean Shader::isCompiled()
{
	return bCompiled;
}

GLint Shader::getAttributeSize()
{
	return iAttributeSize;
}

GLint Shader::getUniformSize()
{
	return iUniformSize;
}

GLvoid Shader::enableVertexAttribute(GLint iLocation)
{
	checkManaged();
	glEnableVertexAttribArray(iLocation);
}

GLvoid Shader::disableVertexAttribute(GLint iLocation)
{
	checkManaged();
	glDisableVertexAttribArray(iLocation);
}

std::string Shader::getAttributeName(GLint iLocation)
{
     return pAttributeNames[iLocation]; 
	/*std::string tempName = mapAttribute[iLocation];
	return tempName;*/
}

std::string Shader::getUniformName(GLint iLocation)
{
	return pUniformNames[iLocation]; 
	/*std::string tempName = mapUniform[iLocation];
	return tempName;*/
}

GLvoid Shader::setUniformf(const std::string sName, GLfloat fValue)
{
	checkManaged();
	GLint iLocation = mapUniform[sName];
	glUniform1f(iLocation, fValue);
}

GLvoid Shader::setVertexAttribute(GLint iLocation, GLint iSize, GLint iType, 
	                              GLboolean bNormalize, GLint iStride, 
								  const GLvoid *pPointer)
{
	checkManaged();
	glVertexAttribPointer(iLocation, iSize, iType, bNormalize, iStride,
                     	  pPointer);
}

GLvoid Shader::deleteShader()
{
	glDeleteShader(iVertexShaderHandle);
	glDeleteShader(iFragmentShaderHandle);
}

GLvoid Shader::dispose()
{
	glDeleteProgram(uiProgramID);	
}















