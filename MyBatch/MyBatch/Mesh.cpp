#include "Mesh.h"

//Create an array of 10 Mesh*
std::vector<Mesh*> Mesh::vMesh(10);

Mesh::Mesh()
	:uiIndexBuffer(0)
	,uiVertexArrayID(0)
	,uiVertexBuffer(0)
{
	indexBufferObject();
	vertexBufferObject();
	addManageMesh();
}

Mesh::~Mesh()
{}

void Mesh::indexBufferObject()
{
	//Generate the index buffer object
	glGenBuffers(1, &uiIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexBuffer);
	//If the index buffer object handle failed
	assert(glIsBuffer(uiIndexBuffer));

	/*if (glIsBuffer(uiIndexBuffer)==GL_FALSE)
	{
		printf("Failed to generate or bind the index buffer.
			  Please try again.\n");
		getchar();
		exit(1);
	}*/
}

void Mesh::vertexBufferObject()
{
	//Generate the vertex array
	glGenVertexArrays(1, &uiVertexArrayID);
	glBindVertexArray(uiVertexArrayID);
	//If the vertex array handle failed
	assert(glIsVertexArray(uiVertexArrayID));

	/*if (glIsVertexArray(uiVertexArrayID)==GL_FALSE)
	{
		fprintf(stderr,"Failed to generate or bind the vertex array.
				Please try again.\n");
		glDeleteBuffers(1,&uiIndexBuffer);
		getchar();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}*/

	//Generate the vertex buffer object
	glGenBuffers(1, &uiVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBuffer);
	//If the vertex buffer object handle failed
	assert(glIsBuffer(uiVertexBuffer));

	/*if (glIsBuffer(uiVertexBuffer)==GL_FALSE)
	{
		fprintf(stderr,"Failed to generate or bind the vertex buffer.
		       Please try again.\n");
		glDeleteBuffers(1,&uiIndexBuffer);
		glDeleteVertexArrays(1,&uiVertexArrayID);
		getchar();
		glfwTerminate();
		exit(EXIT_FAILURE);
	}*/
}

GLvoid Mesh::addManageMesh()
{
	vMesh.push_back(this);
}

GLvoid Mesh::fillIndexData(const GLshort *pIndices, GLint iNumber)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(GLshort) * iNumber) , 
		         pIndices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getIndexID());
}

GLvoid Mesh::fillVertexData(const Vertex *pVertex, GLint iNumber)
{
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(Vertex) * iNumber),
		         pVertex, GL_STATIC_DRAW);
}

GLuint Mesh::getVertexBuffer()
{
	return uiVertexBuffer;
}

GLuint Mesh::getVertexArrayID()
{
	return uiVertexArrayID;
}

GLuint Mesh::getIndexID()
{
	return uiIndexBuffer;
}

GLvoid Mesh::bind(Shader *pShader)
{
	GLint numAttributes = pShader->getAttributeSize();
	assert(numAttributes);

	/*if (numAttributes<0)
	{
		printf("No exit attribute.Please check!\n");
		getchar();
		return ;
	}*/

	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBuffer);

	for (GLint i = 0 ; i < numAttributes ; ++i)
	{
		pShader->enableVertexAttribute(i);
		//===Whether "a_texCoord0"
		if (pShader->getAttributeName(i) == "a_texCoord0")
		{
			pShader->setVertexAttribute(i, 2, GL_FLOAT, GL_FALSE,
				20, (void*)12);
		}
		else
		{
			pShader->setVertexAttribute(i, 3, GL_FLOAT, GL_FALSE,
				20, (void*)0);
		}	
	}
}

GLvoid Mesh::unbind(Shader *pShader)
{
	GLint numAttributes = pShader->getAttributeSize();
	assert(numAttributes);

	/*if (numAttributes<0)
	{
		printf("No exit attribute.Please check!\n");
		getchar();
		return ;
	}*/

	for (GLint i = 0 ; i < numAttributes ; ++i)
	{
		pShader->disableVertexAttribute(i);
	}
}

GLvoid Mesh::render(Shader *pShader, GLint iCount)
{
	bind(pShader);

	//draw triangles
	glDrawElements(GL_TRIANGLES, 6 * iCount, GL_UNSIGNED_SHORT, (GLvoid*) 0);

	unbind(pShader);
}

GLvoid Mesh::dispose()
{
	//Destroy the indexBufferObject
	glDeleteBuffers(1, &uiIndexBuffer);

	//Destroy the VertexArrayObject
	glDeleteVertexArrays(1, &uiVertexArrayID);

	//Destroy the vertexBufferObject
	glDeleteBuffers(1, &uiVertexBuffer);
}
