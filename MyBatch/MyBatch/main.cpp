/***************************************************************************** 
    *  @COPYRIGHT NOTICE 
    *  @Copyright (c) 2016, WuLD 
    *  @All rights reserved 
 
    *  @file     : main.h 
    *  @version  : ver 1.0 
 
    *  @author   : WuLD 
    *  @date     : 2016/4/25 09:54 
    *  @brief    :    
*****************************************************************************/ 
#include "WindowBackground.h"
#include "SpriteBatch.h"
#include "FrameBuffer.h"

int main()
{
	WindowBackground myWindow;

	GLint iWindowWidth  = myWindow.getWindowWidth();
	GLint iWindowHeight = myWindow.getWindowHeight();

	SpriteBatch mySprite;

	Texture myTex;

	myTex.loadTexture("E:/Texture/apple.jpg");

	GLint iTexWidth  = myTex.getTexWidth();
	GLint iTexHeight = myTex.getTexHeight();

	GLfloat fTexWidth  = static_cast<GLfloat> (iTexWidth);
	GLfloat fTexHeight = static_cast<GLfloat> (iTexHeight);

	/*FrameBuffer myFBO(iTexWidth, iTexHeight);
	FrameBuffer myFBO2(iTexWidth, iTexHeight);*/

	GLfloat fTime = 0.0f;

	/* Custom shader */
	Shader myShader("VerDny.vs", "FraDny.fs");
	Shader myShader2("VerAve.vs", "FraAve.fs");

	do 
	{
		/* Set context color */
 		glClearColor(1.0f,0.0f,1.0f,0.0f);
 		/* Clear the color buffer */
 		glClear(GL_COLOR_BUFFER_BIT);

		fTime += 0.1f;

		/*Test the custom default*/
		mySprite.setShader(NULL);
		mySprite.begin();
		mySprite.draw(myTex, 0.0f, 0.0f, 0.0f, 0.0f, (GLfloat)iTexWidth, 
		(GLfloat)iTexHeight, 1.0f, 1.0f, 0.0f, 0, 0, iTexWidth, iTexHeight,
		GL_FALSE, GL_FALSE);
		mySprite.end();

		mySprite.setShader(&myShader2);
		mySprite.begin();
		mySprite.draw(myTex, 300.0f, 100.0f, 0.0f, 0.0f, (GLfloat)iTexWidth, 
		(GLfloat)iTexHeight, 1.0f, 1.0f, 0.0f, 0, 0, iTexWidth, iTexHeight, 
		GL_FALSE, GL_FALSE);
		mySprite.end();

		/*Test the FBO*/
		/*mySprite.begin();
		myFBO.begin();
		mySprite.setShader(NULL);
		mySprite.draw(myTex, 0.0f, 0.0f, 0.0f, 0.0f, fTexWidth, 
		fTexHeight, 1.0f, 1.0f, 0.0f, 0, 0, 
		iTexWidth, iTexHeight, GL_FALSE, GL_FALSE);
		myFBO.end(iWindowWidth, iWindowHeight);
		mySprite.draw(myFBO.getRenderTexture(), 300.0f, 0.0f, 0.0f, 0.0f, 
		fTexWidth, fTexHeight, 1.0f, 1.0f, 
		0.0f, 0, 0, iTexWidth, iTexHeight, GL_FALSE, GL_FALSE);
		mySprite.end();

		mySprite.setShader(&myShader);
		mySprite.begin();	
		myShader.setUniformf("time", fTime);
		mySprite.draw(myFBO.getRenderTexture(), 0.0f, 0.0f, 0.0f, 0.0f, 
		fTexWidth, fTexHeight, 1.0f, 1.0f,  
		0.0f, 0, 0, iTexWidth, iTexHeight, GL_FALSE, GL_FALSE);
		mySprite.end();*/

		/*Test the series-shader */
		/*mySprite.begin();
		myFBO.begin();
		mySprite.setShader(NULL);
		mySprite.draw(myTex, 0.0f, 0.0f, 0.0f, 0.0f, fTexWidth, 
		fTexHeight, 1.0f, 1.0f, 0.0f, 0, 0, 
		iTexWidth, iTexHeight, GL_FALSE, GL_FALSE);
		myFBO.end(iWindowWidth, iWindowHeight);*/
		/*mySprite.draw(myFBO.getRenderTexture(), 0.0f, 0.0f, 0.0f, 0.0f, 
		              fTexWidth, fTexHeight, 1.0f, 1.0f, 
		              0.0f, 0, 0, iTexWidth, iTexHeight, GL_FALSE, GL_FALSE);*/
		//mySprite.end();
		
		/* Swap the front and back buffer */
		glfwSwapBuffers(myWindow.getWindowHandle());
		/* Poll events by query */
		glfwPollEvents();

	} while ( 
	    (glfwGetKey(myWindow.getWindowHandle(), GLFW_KEY_ESCAPE) != GLFW_PRESS) 
		&& (glfwWindowShouldClose(myWindow.getWindowHandle()) == 0) 
		);

	/*myFBO.dispose();*/

	/* Release resources */
	mySprite.dispose();

	/* Destroy the window */
	glfwTerminate();

	return 0;

}

