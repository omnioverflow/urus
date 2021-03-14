#include "application.h"

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "engine/graphics/shader.h"
#include "engine/graphics/texture_loader.h"
#include "engine/window/window.h"
#ifndef NDEBUG
#include "engine/window/console.h"
#endif

using namespace urus;

GLuint Application::VAO;
GLuint Application::VBO;
GLuint Application::texture;
std::unique_ptr<ShaderProgram> Application::shaders[NB_SHADERS];

Application::Application()
: mTexLoader(nullptr)
, mWindow(nullptr)
{
}

Application::~Application()
{
	try 
	{
		shutdown();  
	}
	catch(const std::exception& ex) 
	{
		// swallow 
		std::cerr << "shutdown failed " << ex.what() << std::endl;
	}  
}

bool Application::setup(int argc, char* argv[])
{
	if (!mWindow)
	{
		std::cerr << "[error] No window has been set" << std::endl;
		assert(false);
	}
	glutInit(&argc, argv);
#ifdef __APPLE__
    // FIXME: GLUT was deprecated on mac os :(
#elif _WIN64
    glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	int contextFlags = GLUT_FORWARD_COMPATIBLE;
#ifdef NDEBUG
//	contextFlags |= GLUT_DEBUG;
#endif

	glutInitContextFlags(contextFlags);
    
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

    auto displayMode = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
#ifdef __APPLE__
    /*
     To activate core profile 3.2+,
     instead of glutInitContextVersion(), add the GLUT_3_2_CORE_PROFILE to  glutInitDisplayMode()
     */
    displayMode |= GLUT_3_2_CORE_PROFILE;
#endif
    
	glutInitDisplayMode(displayMode);
	glutCreateWindow(mWindow->title().c_str());

	glutIdleFunc(idle);
	glutDisplayFunc(render);
	glutVisibilityFunc(visible);
	/*
	   glutReshapeFunc(reshape);
	   glutKeyboardFunc(keyboardCallback);
	   glutMouseFunc(mouseCallback);
	   glutMouseWheelFunc(mouseWheelCallback);	   
	   glutIdleFunc(animate);
	 */

#ifdef _WIN64
	glewExperimental = true;
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) 
	{
		std::cerr << "ERROR: %s\n" << glewGetErrorString(GlewInitResult);
	}
#endif
    
	std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) 
		<< " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	int maxNbAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxNbAttribs);
	std::cout << "Max number of attribs supported on the current hardware: " << maxNbAttribs << "\n";

	glEnable(GL_DEPTH_TEST); // what the heck?

	float vertices[] = {
		// xyz rgb st (uv)
		 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, // bottom left 
		 -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f // top left
	};

	// indices for index drawing
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Generate all VBOs and VAOs
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	GLuint EBO; // Element Buffer Object
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	
	const GLsizei stride = 8 * sizeof(float);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// populate the EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// load shaders
	shaders[0] = std::make_unique<ShaderProgram>("shader0.vert", "shader0.frag");
	shaders[1] = std::make_unique<ShaderProgram>("shader1.vert", "shader1.frag");
	
	// setup textures
	{
        mTexLoader = std::make_shared<TextureLoader>("assets/container.jpg");
        
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
        
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (mTexLoader->isTexLoaded())
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mTexLoader->texWidth(), mTexLoader->texHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, mTexLoader->texData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	return true;
}

void Application::render()
{
	// FIXME: remove render count (debug info)
	static GLuint renderCount = 0;
	std::cout << "Render count: " << renderCount++ << "\n";
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);

	shaders[0]->useProgram();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0 /* offset */);

	shaders[1]->useProgram();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)) /* offset*/);

	// Note, an implicit glFlush is done by glutSwapBuffers before it returns
	glutSwapBuffers();
}

void Application::shutdown()
{
	// TODO: release all resources
}


void Application::run()
{
	glutMainLoop();
}

void Application::updateWindowPositionAndBounds() const
{
	if (mWindow)
		mWindow->updateWindowPositionAndBounds();

#ifndef NDEBUG
	if (mConsole)
		mConsole->updateWindowPositionAndBounds();
#endif
}

void Application::idle()
{
	// Mark the window for redisplay the next iteration through glutMainLoop 
	glutPostRedisplay();
}

void Application::keyboardCallback(unsigned char key, int x, int y)
{
	// FIXME: implement
}

void Application::mouseCallback(int button, int state, int x, int y)
{
	// FIXME: implement
}

void Application::mouseWheelCallback(int wheel, int direction, int x, int y)
{
	// FIXME: implement
}

void Application::animate()
{
	// FIXME: implement
}

void Application::reshape(int width, int height)
{
	return;
	auto window = sharedInstance().window();
	if (window)
		window->setWindowBounds(width, height);

	// Update transformation from NDC (Normalised Device Coordinates)
	// to WC (Window Coordinates)
	glViewport(0, 0, width, height);
}

void Application::visible(int isVisible)
{
	// Disable the call to idle func, when the window is not visible
	if (isVisible == GLUT_VISIBLE)
		glutIdleFunc(idle);
	else
		glutIdleFunc(0);
}
