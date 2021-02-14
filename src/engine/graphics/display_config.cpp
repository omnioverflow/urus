#include "display_config.h"

#ifdef _WIN64
#include <windows.h>
#elif __APPLE__
#include <CoreGraphics/CGDisplayConfiguration.h>
#else
// Force compilation failure, as only supported implementations
// for the moment are _WIN64 and __APPLE__ platforms
#include <assert.h>
static_assert(false);
#endif

using namespace urus;

int DisplayConfig::getScreenWidth()
{
	//mWindowWidth = glutGet(GLUT_SCREEN_WIDTH);
#ifdef _WIN64
	return GetSystemMetrics(SM_CXSCREEN);
#else
	return CGDisplayPixelsWide(CGMainDisplayID());
#endif
}

int DisplayConfig::getScreenHeight()
{
	//mWindowHeight = glutGet(GLUT_SCREEN_HEIGHT);
#ifdef _WIN64
	return GetSystemMetrics(SM_CYSCREEN);
#else
	return CGDisplayPixelsHigh(CGMainDisplayID());
#endif
}
