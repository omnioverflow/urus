#include "Game.h"

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"
#include "game/model/GameWorld.h"
#include "game/view/Views.h"

using namespace urus;

GLuint Game::VAO;
GLuint Game::VBO;
Texture* Game::sTexture;
std::unique_ptr<ShaderProgram> Game::shaders[NB_SHADERS];

// ============================================================================
// Game::GlutDispatcher impl
// ============================================================================

void Game::GlutDispatcher::displayFunc()
{
	urus::Game::sharedInstance().render();
}

void Game::GlutDispatcher::idleFunc()
{
	urus::Game::sharedInstance().animate();
}

void Game::GlutDispatcher::keyboardFunc(unsigned char key, int x, int y)
{
	// FIXME: provide impl
}

void Game::GlutDispatcher::mouseFunc(int button, int state, int x, int y)
{
	// FIXME: provide impl
}

void Game::GlutDispatcher::mouseWheelFunc(int wheel, int direction, int x, int y)
{
	// FIXME: provide impl
}

void Game::GlutDispatcher::reshapeFunc(int width, int height)
{
	// FIXME: provide impl
}

void Game::GlutDispatcher::visibilityFunc(int isVisible)
{
	urus::Game::sharedInstance().visible(isVisible);
}

// ============================================================================
// Game impl
// ============================================================================

Game::Game() : mGameView(nullptr) 
{}

Game::~Game()
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

void Game::createView(int argc, char* argv[])
{
	if (!mGameView)
	{
		std::cerr << "[error] No view was set" << std::endl;
		assert(false);
	}

	glutInit(&argc, argv);
#ifdef __APPLE__
    // FIXME: GLUT was deprecated on mac os :(
#elif _WIN64
    glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	int contextFlags = GLUT_FORWARD_COMPATIBLE;
#if !defined(NDEBUG)
	contextFlags |= GLUT_DEBUG;
#endif // NDEBUG

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
	glutCreateWindow(mGameView->title().c_str());

	glutIdleFunc(GlutDispatcher::idleFunc);
	glutDisplayFunc(GlutDispatcher::displayFunc);
	glutVisibilityFunc(GlutDispatcher::visibilityFunc);
	
	/*
	   glutReshapeFunc(reshape);
	   glutKeyboardFunc(keyboardCallback);
	   glutMouseFunc(mouseCallback);
	   glutMouseWheelFunc(mouseWheelCallback);	   
	   glutIdleFunc(animate);
	 */

#ifdef _WIN64
	GLint GlewInitResult = glewInit();
	if (GlewInitResult != GLEW_OK) 
		std::cerr << "ERROR: %s\n" << glewGetErrorString(GlewInitResult);
#endif
    
	std::cout << "OpenGL initialized: OpenGL version: " << glGetString(GL_VERSION) 
		<< " GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	int maxNbAttribs;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxNbAttribs);
	std::cout << "Max number of attribs supported on the current hardware: " << maxNbAttribs << "\n";

	glEnable(GL_DEPTH_TEST); // what the heck?
}

void Game::loadResources()
{
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
	sTexture = new Texture("assets/container.jpg", GL_RGB, GL_RGB);
}

void Game::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	sTexture->use();

	glBindVertexArray(VAO);

	shaders[0]->useProgram();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0 /* offset */);

	shaders[1]->useProgram();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)) /* offset*/);

	// Note, an implicit glFlush is done by glutSwapBuffers before it returns
	glutSwapBuffers();
}

void Game::shutdown()
{
	// TODO: release all resources
}

int Game::run()
{
	glutMainLoop();

	return 0;
}

void Game::updateViewPositionAndBounds() const
{
	if (mGameView)
		mGameView->updateViewPositionAndBounds();

#if !defined(NDEBUG)
	if (mConsoleView)
		mConsoleView->updateViewPositionAndBounds();
#endif // NDEBUG
}

void Game::idle()
{
	// Mark the window for redisplay the next iteration through glutMainLoop 
	glutPostRedisplay();
}

void Game::keyboardCallback(unsigned char key, int x, int y)
{
	// FIXME: implement
}

void Game::mouseCallback(int button, int state, int x, int y)
{
	// FIXME: implement
}

void Game::mouseWheelCallback(int wheel, int direction, int x, int y)
{
	// FIXME: implement
}

void Game::animate()
{
	// FIXME: implement
}

void Game::reshape(int width, int height)
{
	// FIXME: remove early exit
	return;
	GameView& gameView = sharedInstance().gameView();
	gameView.setViewBounds(width, height);

	// Update transformation from NDC (Normalised Device Coordinates)
	// to WC (Window Coordinates)
	glViewport(0, 0, width, height);
}

void Game::visible(int isVisible)
{
	// Disable the call to idle func, when the window is not visible
	if (isVisible == GLUT_VISIBLE)
		glutIdleFunc(idle);
	else
		glutIdleFunc(0);
}

GameView& Game::gameView() const
{
	return *mGameView;
}

void Game::setGameView(std::unique_ptr<GameView> gameView)
{
	mGameView = std::move(gameView);
}

GameWorld& Game::gameWorld() const
{
	return *mGameWorld;
}

void Game::setGameWorld(std::unique_ptr<GameWorld> gameWorld)
{
	mGameWorld = std::move(gameWorld);
}

#if !defined(NDEBUG)
void Game::setConsoleView(std::unique_ptr<ConsoleView> consoleView)
{
	mConsoleView = std::move(consoleView);
}
#endif