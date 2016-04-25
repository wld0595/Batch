#include "WindowBackground.h"

WindowBackground::WindowBackground()
	:pWindowHandle(NULL)
	,iWindowWidth(960)
	,iWindowHeight(512)
	,pWindowTitle("New Window")
{
	/* initi the run environment */
	initi();
}


/* Construction function:initialized the member variable */
WindowBackground::WindowBackground(GLFWwindow *pWindow, GLint iWidth,
	                               GLint iHeight, GLchar *pTitle)
	:pWindowHandle(pWindow)
	,iWindowWidth(iWidth)
	,iWindowHeight(iHeight)
	,pWindowTitle(pTitle)
{
	/* initi the run environment */
	initi();
}

WindowBackground::~WindowBackground()
{
	pWindowHandle = NULL;
	pWindowTitle  = NULL;
}

void WindowBackground::setWindow(GLFWwindow *pWindow, GLint iWidth, 
	                             GLint iHeight, GLchar *cpTitle)
{
	pWindowHandle = pWindow;
	iWindowWidth  = iWidth;
	iWindowHeight = iHeight;
	pWindowTitle  = cpTitle;
}

void WindowBackground::initi()
{
	/* initialized the GLFW */
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to the initialized GLFW.\n");
		return ;
	}
	/* Set some hints */
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create window */
	pWindowHandle = glfwCreateWindow(iWindowWidth, iWindowHeight,  
	                                 pWindowTitle, NULL, NULL);
	if (pWindowHandle == NULL)/* Failed to the create window */
	{
		fprintf(stderr, "Failed to the create window.\n");
		getchar();
		return ;
	}
	/* Make the context of current window */
	glfwMakeContextCurrent(pWindowHandle);

	/* initialized the GLEW */
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)/* Failed to initialized the GLEW */
	{
		fprintf(stderr, "Failed to the initialized the GLEW.\n");
		getchar();
		return ;
	}
	/* Set the input mode is key */
	glfwSetInputMode(pWindowHandle, GLFW_STICKY_KEYS, GL_TRUE);
}

GLint WindowBackground::getWindowWidth()
{
	return iWindowWidth;
}

GLint WindowBackground::getWindowHeight()
{
	return iWindowHeight;
}

GLFWwindow* WindowBackground::getWindowHandle()
{
	return pWindowHandle;
}

/* Change the window size by orthographic projection */
void WindowBackground::changeWindowSize()
{
	GLfloat fAspectRatio = 0.0f;

	if (iWindowHeight == 0)
	{
		iWindowHeight = 1;
	}
	glViewport(0, 0, iWindowWidth, iWindowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fWidth  = static_cast<GLfloat> (iWindowWidth);
	GLfloat fHeight = static_cast<GLfloat> (iWindowHeight);
	fAspectRatio =  fWidth / fHeight;
	if (iWindowWidth <= iWindowHeight)
	{
		glOrtho(0.0f, fWidth, 0.0f, 
		        (iWindowHeight / fAspectRatio), 1.0f, -1.0f);
	}
	else
	{
		glOrtho(0.0f, (iWindowWidth * fAspectRatio), 0.0f, 
		        fHeight, 1.0f, -1.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

