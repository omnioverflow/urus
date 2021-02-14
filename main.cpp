#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "application/application.h"
#include "application/viewer.h"
#include "engine/graphics/display_config.h"
#include "engine/graphics/shader.h"
#include "engine/window/window.h"

#ifndef NDEBUG
#include "engine/window/console.h"
#endif

// FIXME: avoid mixing with glabal namespace
//using namespace util; // FIXME: no need?

// ----------------------------------------------------------------------------
//
// FIXME: refactor to get rid of GLOB vars
bool firstLoad = true;
//Mat4f scaleMatrix;
//Mat4f rotationMatrix;
//Vec4f centerOfRotation{0.0f, 0.0f, 0.0f};
//
// ----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	std::cout << urus::DisplayConfig::getScreenWidth() << ", ";
	std::cout << urus::DisplayConfig::getScreenHeight() << std::endl;

	// FIXME: use appropriate subclasses for the specific applications
	auto& app = urus::Application::sharedInstance();
	auto window = std::make_shared<urus::Window>(std::string("Core OpenGL 4.3 Example"));
	window->snapWindowPosition(urus::WindowPosition::TOP_RIGHT);
	app.setWindow(window);
#ifndef NDEBUG
	auto console = std::make_shared<urus::Console>();
	console->snapWindowPosition(urus::WindowPosition::BOTTOM_RIGHT);
	app.setConsole(console);
#endif

	app.setup(argc, argv);
	app.updateWindowPositionAndBounds();

	app.run();
	app.shutdown();
}

/*
   void loadShaders();
   GLuint loadShader(const std::string& vertShaderName, const std::string& fragShaderName, GLuint shaderId);
   void drawCoordinateSystem(GLuint shaderProg, GLuint shaderId);
   void renderFrame();
   void keyboardCallback(unsigned char key, int x, int y);
   void mouseCallback(int button, int state, int x, int y);
   void mouseWheelCallback(int wheel, int direction, int x, int y);
   void animate();
   void reshape(int W, int H);
   void visible(int vis);

   void render()
   {

   }

//
//==============================================================================

//==============================================================================
//
void drawCoordinateSystem(GLuint shaderProg, GLuint shaderId) {
glUseProgram(shaderProg);
glBindVertexArray(VAOs[1]);
glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);

auto uniformsCopy = ShaderUniforms[shaderId];
glUniformMatrix4fv(uniformsCopy["scaleMatrix"], 1, GL_FALSE, scaleMatrix.data()->data());
glUniformMatrix4fv(uniformsCopy["rotationMatrix"], 1, GL_FALSE, rotationMatrix.data()->data());

glEnable(GL_LINE_SMOOTH);
glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
glDrawArrays(GL_LINES, 0, 6);
}
//
//==============================================================================

//==============================================================================
//
void renderFrame() {
glClearColor(0.0, 0.0, 0.0, 1.0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// glClear(GL_DEPTH); // <-- Bug - this trigger a debug callback

if (firstLoad) {
scaleMatrix = getIdentity4f();
rotationMatrix = getIdentity4f();
firstLoad = false;
}

// Draw triangles
{
const float timeScale = 0.008f;

const auto shaderId = 0;
glUseProgram(ShaderPrograms[shaderId]);

glBindVertexArray(VAOs[0]);

auto uniformsCopy = ShaderUniforms[shaderId];

//GLfloat timeValue = glutGet(GLUT_ELAPSED_TIME) * timeScale;
//vec2 p(0.5f * sinf(timeValue), 0.5f * cosf(timeValue));
//glUniform2fv(uniformsCopy["p"], 1, p);

glUniformMatrix4fv(uniformsCopy["scaleMatrix"], 1, GL_FALSE, scaleMatrix.data()->data());
glUniformMatrix4fv(uniformsCopy["rotationMatrix"], 1, GL_FALSE, rotationMatrix.data()->data());

glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

// Draw coordinate system
{
	drawCoordinateSystem(ShaderPrograms[1], 1);
}

// Note, an implicit glFlush is done by glutSwapBuffers before it returns
glutSwapBuffers();
}

*/

/*
//------------------------------------------------------------------------------
//
void reshape(int W, int H) {
WINDOW_WIDTH = W;
WINDOW_HEIGHT = H;
glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void animate() {
glutPostRedisplay();
}

void visible(int vis) {
if (vis == GLUT_VISIBLE)
glutIdleFunc(animate);
else
glutIdleFunc(0);
}

void APIENTRY openglCallbackFunction(GLenum source, GLenum type, GLuint id, GLenum severity,
GLsizei length, const GLchar* message, void* userParam) {
}
//
//------------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//------------------------------------------------------------------------------
//
void mouseCallback(int button, int state, int x, int y) {
static Vec3i prevMousePos;

// TODO: implement
std::cout << "Mouse button";
if (button == GLUT_LEFT_BUTTON)
std::cout << " LEFT_BUTTON";
else if (button == GLUT_RIGHT_BUTTON)
std::cout << " RIGHT_BUTTON";
else if (button == GLUT_MIDDLE_BUTTON)
std::cout << " MIDDLE_BUTTON";

std::string stateStr;
if (state == GLUT_DOWN) {
stateStr = "GLUT_DOWN"; 
prevMousePos[0] = x;
prevMousePos[1] = y;
}
else if (state == GLUT_UP) {
stateStr = "GLUT_UP";
const auto prevPos = ViewTransform::toEyespace(prevMousePos, WINDOW_WIDTH, WINDOW_HEIGHT);
Vec3i currMousePos{ x, y, 1 };
const auto currPos = ViewTransform::toEyespace(currMousePos, WINDOW_WIDTH, WINDOW_HEIGHT);

// rotate view matrix according to mouse movement
auto prevTrackpad = Vec4fFactory::asVec4f(prevPos);
prevTrackpad[2] = sqrt(1.0f - prevTrackpad[0] * prevTrackpad[0] - prevTrackpad[1] * prevTrackpad[1]);
auto currTrackpad = Vec4fFactory::asVec4f(currPos);
currTrackpad[2] = sqrt(1.0f - currTrackpad[0] * currTrackpad[0] - currTrackpad[1] * currTrackpad[1]);

const auto rotationAxis = cross(prevTrackpad, currTrackpad);
std::cout << std::endl << "rotation axis {" << rotationAxis[0] << ", " << rotationAxis[1] <<
", " << rotationAxis[2] << ", " << rotationAxis[3] << "}" << std::endl;
int yoloCruiser = 0;

rotationMatrix = rotv(rotationAxis, 1.0f);
}

std::cout << " at " << x << ", " << y << ", state " << stateStr << std::endl;
}

void mouseWheelCallback(int wheel, int direction, int x, int y) {
std::cout << "Mouse wheel " << wheel;
if (direction >= 0) {
	std::cout << " UP ";

	const float scaleFactor = 0.9f;
	scaleMatrix[0][0] *= scaleFactor;
	scaleMatrix[1][1] = scaleMatrix[0][0];
	scaleMatrix[2][2] = scaleMatrix[0][0];
}
else if (direction < 0) {
	std::cout << " DOWN";

	const float scaleFactor = 1.1f;
	scaleMatrix[0][0] *= scaleFactor;
	scaleMatrix[1][1] = scaleMatrix[0][0];
	scaleMatrix[2][2] = scaleMatrix[0][0];
}

glutPostRedisplay();

std::cout << " at " << x << ", " << y << std::endl;
std::cout << "Current scale " << scaleMatrix[0][0] << std::endl;
}
//
//------------------------------------------------------------------------------
//
void keyboardCallback(unsigned char key, int x, int y) {
	// TODO: implement
	std::cout << "Key pressed " << key << " at " << x << ", " << y << std::endl;

	// const auto R = getRotation({0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f});
	// print(R);

	const float timeScale = 0.008f;
	GLfloat timeValue = glutGet(GLUT_ELAPSED_TIME) * timeScale;

	const float PI = 3.14f;
	const auto theta = timeValue;
	Mat4f Rx = {
		Vec4f{1.0f, 0.0f      , 0.0f        , 0.0f},
		Vec4f{0.0f, cos(theta), -sin(theta) , 0.0f},
		Vec4f{0.0f, sin(theta), cos(theta)  , 0.0f},
		Vec4f{0.0f, 0.0f      , 0.0f        , 1.0f}
	};
	Mat4f Rz = {
		Vec4f{cos(theta) , sin(theta), 0.0f, 0.0f},
		Vec4f{-sin(theta), cos(theta), 0.0f, 0.0f},
		Vec4f{0.0f       , 0.0f      , 0.0f, 0.0f},
		Vec4f{0.0f       , 0.0f      , 0.0f, 1.0f}
	};
	Mat4f Ry = {
		Vec4f{cos(theta), 0.0f, sin(theta), 0.0f},
		Vec4f{0.0f      , 1.0f, 0.0f      , 0.0f},
		Vec4f{sin(theta), 0.0f, cos(theta), 0.0f},
		Vec4f{0.0f      , 0.0f, 0.0f      , 1.0f}
	};
	auto R = mult(Rx, Rz);
	R = mult(R, Ry);
	print(R);
	rotationMatrix = R;

	glutPostRedisplay();
}
//
//------------------------------------------------------------------------------

*/
