#include "Batch.h"

Batch::Batch()
{}

Batch::~Batch()
{}

GLvoid Batch::begin()
{}

GLvoid Batch::end()
{}

GLvoid Batch::draw(const Texture &texture, GLfloat x, GLfloat y, 
	               GLfloat originX, GLfloat originY, GLfloat width,  
	               GLfloat height, GLfloat scaleX, GLfloat scaleY,  
				   GLfloat rotation, GLint srcX, GLint srcY, GLint srcWidth,
	               GLint srcHeight, GLboolean flipX, GLboolean flipY)
{}

GLvoid Batch::flush()
{}

GLvoid Batch::setShader(Shader *shader)
{}

GLboolean Batch::isDrawing()
{
	return GL_FALSE;
}

GLvoid Batch::dispose()
{}