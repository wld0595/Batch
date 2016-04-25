#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
	:miSize(10)/*Set ten sprite batch */
	,mbDrawing(GL_FALSE)
	,mpVertices(NULL)
	,mpIndices(NULL)
	,miRenderCalls(0)
	,miTotalRenderCalls(0)
	,miCount(0)
	,mfInvTexWidth(0.0f)
	,mfInvTexHeight(0.0f)
	,mDefaultShader(NULL)
	,mCustomShader(NULL)
	,miMatrixID(-1)
	,miTextureID(-1)
	,mModelMatrix(glm::mat4(1.0f))
	,mProjectionMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 512.0f, 0.0f, 100.0f))
	,miMaxSpritesInBatch(0)
	
{
	/* Set the projection matrix is default size of window */
	/*mProjectionMatrix=glm::ortho(0.0f, 960.0f, 0.0f, 512.0f, 0.0f, 100.0f);

	mModelMatrix = glm::mat4(1.0f);*/

	mpVertices = new Vertex[miSize * 4];

	/* Set the indices array */
	GLint iLength = miSize * 6;
	mpIndices  = new GLshort[iLength];
	GLshort j  = 0;
	/* Calculate the index data */
	for (GLint i = 0;i<iLength; i += 6 , j += 4)
	{
		mpIndices[i]   = j;
		mpIndices[i + 1] = (GLshort)(j+1);
		mpIndices[i + 2] = (GLshort)(j+2);
		mpIndices[i + 3] = (GLshort)(j+2);
		mpIndices[i + 4] = (GLshort)(j+3);
		mpIndices[i + 5] = j;
	}

	mDefaultShader = createDefaultShader();
}

SpriteBatch::~SpriteBatch()
{
	delete [] mpVertices;
	delete [] mpIndices;
	/*delete mDefaultShader;
	delete mCustomShader;*/
}

Shader* SpriteBatch::createDefaultShader()
{
	static const std::string VertexShader=
		"#version 330 core\n"
		"in vec3 a_position;\n"
		"in vec2 a_texCoord0;\n"
		"out vec2 v_texCoords;\n"
		"uniform mat4 u_projTrans;\n"
		"void main() {\n "
		"gl_Position =  u_projTrans * vec4(a_position,1);\n"
		"v_texCoords = a_texCoord0;\n"
		"}\n";

	static const std::string FragmentShader =
		"#version 330 core\n" 
		"in vec2 v_texCoords;\n"
		"out vec3 color;\n"
		"uniform sampler2D u_texture;\n "
		"void main() {\n"
		"color = texture(u_texture,v_texCoords).rgb;\n"
		"}\n";

	Shader* tempShader = new Shader(VertexShader,FragmentShader);
	assert(tempShader->isCompiled());
	/*if (tempShader->isCompiled()==GL_FALSE)
	{
		printf("Error compiling shader.\n");
		getchar();
	}*/

	return tempShader;
}

GLvoid SpriteBatch::begin()
{
	assert(!mbDrawing);
	/*if (mbDrawing)
	{
		printf("Please call SpriteBatch begin firstly.\n");
		return ;
	}*/

	miRenderCalls = 0;

	/* Activate the shader */
	if (mCustomShader != NULL)
	{
		mCustomShader->begin();
	}
	else
	{
		mDefaultShader->begin();
	}
	
	/* Set the project matrix */
	setupMatrices();

	mbDrawing = GL_TRUE;
}

GLvoid SpriteBatch::end()
{
	assert(mbDrawing);
	/*if (!mbDrawing)
	{
		printf("Spritebatch.begin must be called before end.\n");
		return ;
	}*/

	if (miCount>0)
	{
		flush();
	}

	mbDrawing = GL_FALSE;

	if (mCustomShader != NULL)
	{
		mCustomShader->end();
	}
	else
	{
		mDefaultShader->end();
	}
}

GLvoid SpriteBatch::setupMatrices()
{
	mMVP = mProjectionMatrix * mModelMatrix;
	if (mCustomShader != NULL)
	{
		miMatrixID = mCustomShader->fetchUniformLocation("u_projTrans");
		glUniformMatrix4fv(miMatrixID, 1, GL_FALSE, &mMVP[0][0]);
		miTextureID = mCustomShader->fetchUniformLocation("u_texture");
		glUniform1i(miTextureID, 0);
	}
	else
	{
		miMatrixID = mDefaultShader->fetchUniformLocation("u_projTrans");
		glUniformMatrix4fv(miMatrixID, 1, GL_FALSE, &mMVP[0][0]);
		miTextureID = mDefaultShader->fetchUniformLocation("u_texture");
		glUniform1i(miTextureID, 0);
	}
}

GLvoid SpriteBatch::draw(const Texture &texture, GLfloat x, GLfloat y, 
                         GLfloat originX, GLfloat originY, GLfloat width,  
	                     GLfloat height, GLfloat scaleX, GLfloat scaleY, 
						 GLfloat rotation, GLint srcX, GLint srcY, 
						 GLint srcWidth, GLint srcHeight, GLboolean flipX,
	                     GLboolean flipY)
{
	assert(mbDrawing);

	/*if (!mbDrawing)
	{
		printf("Please call batch.begin firstly.\n");
		return ;
	}*/

	if(mLastTexture.notEqual(texture))
	{
		switchTexture(texture);
	}
	else if (miCount == (miSize * 4))
	{
		flush();
	}

	/* Bottom left and top right corner points relative to origin */
	GLfloat worldOriginX = x + originX;
	GLfloat worldOriginY = y + originY;
	GLfloat fx  = -originX;
	GLfloat fy  = -originY;
	GLfloat fx2 = width - originX;
	GLfloat fy2 = height - originY;

	/* Scale */
	if( (scaleX != 1) || (scaleY != 1) )
	{
		fx  *= scaleX;
		fy  *= scaleY;
		fx2 *= scaleX;
		fy2 *= scaleY;
	}

	/* Construct corner points,start from top left and go counter clockwise */
	GLfloat p1x = fx;
	GLfloat p1y = fy;
	GLfloat p2x = fx;
	GLfloat p2y = fy2;
	GLfloat p3x = fx2;
	GLfloat p3y = fy2;
	GLfloat p4x = fx2;
	GLfloat p4y = fy;

	GLfloat x1 = 0.0f; 
	GLfloat y1 = 0.0f;
	GLfloat x2 = 0.0f;
	GLfloat y2 = 0.0f;
	GLfloat x3 = 0.0f;
	GLfloat y3 = 0.0f; 
	GLfloat x4 = 0.0f;
	GLfloat y4 = 0.0f;

	/* Rotate */
	if (rotation != 0)
	{
		GLfloat fcos = cos(rotation);
		GLfloat fsin = sin(rotation);

		x1 = fcos * p1x - fsin * p1y;
		y1 = fsin * p1x + fcos * p1y;

		x2 = fcos * p2x - fsin * p2y;
		y2 = fsin * p2x + fcos * p2y;

		x3 = fcos * p3x - fsin * p3y;
		y3 = fsin * p3x + fcos * p3y;

		x4 = x1 + (x3 - x2);
		y4 = y3 - (y2 - y1);

	}
	else
	{
		x1 = p1x;
		y1 = p1y;

		x2 = p2x;
		y2 = p2y;

		x3 = p3x;
		y3 = p3y;

		x4 = p4x;
		y4 = p4y;
	}

	x1 += worldOriginX;
	y1 += worldOriginY;

	x2 += worldOriginX;
	y2 += worldOriginY;

	x3 += worldOriginX;
	y3 += worldOriginY;

	x4 += worldOriginX;
	y4 += worldOriginY;

	GLfloat u  = srcX * mfInvTexWidth;
	GLfloat v  = (srcY + srcHeight) * mfInvTexHeight;
	GLfloat u2 = (srcX + srcWidth) * mfInvTexWidth;
	GLfloat v2 = srcY * mfInvTexHeight;

	/* Flip */
	if(flipX)
	{
		GLfloat tmp = u;
		u  = u2;
		u2 = tmp;
	}

	if(flipY)
	{
		GLfloat tmp = v;
		v  = v2;
		v2 = tmp;
	}

	/* Calculate the vertex data */
	mpVertices[miCount].x = x1;
	mpVertices[miCount].y = y1;
	mpVertices[miCount].z = 0.0f;
	mpVertices[miCount].u = u;
	mpVertices[miCount].v = v;

	++miCount;

	mpVertices[miCount].x = x2;
	mpVertices[miCount].y = y2;
	mpVertices[miCount].z = 0.0f;
	mpVertices[miCount].u = u;
	mpVertices[miCount].v = v2;

	++miCount;

	mpVertices[miCount].x = x3;
	mpVertices[miCount].y = y3;
	mpVertices[miCount].z = 0.0f;
	mpVertices[miCount].u = u2;
	mpVertices[miCount].v = v2;

	++miCount;

	mpVertices[miCount].x = x4;
	mpVertices[miCount].y = y4;
	mpVertices[miCount].z = 0.0f;
	mpVertices[miCount].u = u2;
	mpVertices[miCount].v = v;

	++miCount;
}

GLvoid SpriteBatch::switchTexture(const Texture &texture)
{
	flush();
	mLastTexture   = texture;
	mfInvTexWidth  = 1.0f / static_cast<GLfloat> (mLastTexture.getTexWidth());
	mfInvTexHeight = 1.0f / static_cast<GLfloat> (mLastTexture.getTexHeight());

}

GLvoid SpriteBatch::flush()
{
	if (miCount == 0)
	{
		return ;
	}

	++miRenderCalls;
	++miTotalRenderCalls;

	GLint spritesInBatch = miCount / 4;

	if (spritesInBatch > miMaxSpritesInBatch)
	{
		miMaxSpritesInBatch = spritesInBatch;
	}
	/* int count=spritesInBatch*6; */

	/* Activate the texture unit and bind texture */
	mLastTexture.bind();

	mMesh.fillVertexData(mpVertices, spritesInBatch * 4);

	mMesh.fillIndexData(mpIndices, spritesInBatch * 6);

	if (mCustomShader != NULL)
	{
		mMesh.render(mCustomShader, spritesInBatch);
	}
	else
	{
		mMesh.render(mDefaultShader, spritesInBatch);
	}
	
	miCount = 0;
}

GLvoid SpriteBatch::setShader(Shader *pShader)
{
	if (mbDrawing)
	{
		flush();
		if (mCustomShader != NULL)
		{
			mCustomShader->end();
		}
		else
		{
			mDefaultShader->end();
		}
	}
	mCustomShader = pShader;
	if (mbDrawing)
	{
		if (mCustomShader != NULL)
		{
			mCustomShader->begin();
		}
		else
		{
			mDefaultShader->begin();
		}
		setupMatrices();
	}
}

Shader* SpriteBatch::getShader()
{
	return (mCustomShader == NULL? mDefaultShader : mCustomShader );

	/*if (mCustomShader==NULL)
	{
		return mDefaultShader;
	}
	return mCustomShader;*/
}

GLboolean SpriteBatch::isDrawing()
{
	return mbDrawing;
}

GLvoid SpriteBatch::setProjectionMatrix(GLfloat fLeft, GLfloat fRight,
	                                    GLfloat fBottom, GLfloat fUp, 
										GLfloat fNear, GLfloat fFar)
{
	mProjectionMatrix = glm::ortho(fLeft, fRight, fBottom, fUp, fNear, fFar);
}

GLvoid SpriteBatch::dispose()
{
	mMesh.dispose();
	mLastTexture.deleteTexture();

	if (mDefaultShader != NULL)
	{
		mDefaultShader->dispose();
	}
	if (mCustomShader != NULL)
	{
		mCustomShader->dispose();
	}
}



