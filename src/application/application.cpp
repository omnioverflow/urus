#include "application.h"

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <windows.h>

#include "engine/graphics/shader.h"
#include "engine/window/window.h"

#ifndef NDEBUG
#include "engine/window/console.h"
#endif

using namespace urus;

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
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	int contextFlags = GLUT_FORWARD_COMPATIBLE;
#ifndef NDEBUG
	contextFlags |= GLUT_DEBUG;
#endif

	glutInitContextFlags(contextFlags);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(mWindow->title().c_str());

	glutDisplayFunc(render);
	/*
	   glutReshapeFunc(reshape);
	   glutKeyboardFunc(keyboardCallback);
	   glutMouseFunc(mouseCallback);
	   glutMouseWheelFunc(mouseWheelCallback);
	   glutVisibilityFunc(visible);
	   glutIdleFunc(animate);
	 */

	glewExperimental = true;
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) 
	{
		std::cerr << "ERROR: %s\n" << glewGetErrorString(GlewInitResult);
	}

	std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) 
		<< " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);

	//loadShaders();
	//loadBufferData();

	return true;
}

void Application::shutdown()
{
	// TODO: release resources
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

void Application::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Note, an implicit glFlush is done by glutSwapBuffers before it returns
	glutSwapBuffers();
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

void Application::visible(int vis)
{
	// FIXME: implement
}
