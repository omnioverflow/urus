#include "display_config.h"

#include <iostream>

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

int DisplayConfig::getScreenWidthPx()
{
	//mWindowWidth = glutGet(GLUT_SCREEN_WIDTH);
#ifdef _WIN64
	return GetSystemMetrics(SM_CXSCREEN);
#else
	return CGDisplayPixelsWide(CGMainDisplayID());
#endif
}

int DisplayConfig::getScreenHeightPx()
{
	//mWindowHeight = glutGet(GLUT_SCREEN_HEIGHT);
#ifdef _WIN64
	return GetSystemMetrics(SM_CYSCREEN);
#else
	return CGDisplayPixelsHigh(CGMainDisplayID());
#endif
}

void DisplayConfig::logScreenInfo()
{
	const auto units = "px";
	std::cout << "Screen width:  " << urus::DisplayConfig::getScreenWidthPx();
	std::cout << " " << units << ",\n";
	std::cout << "Screen height: " << urus::DisplayConfig::getScreenHeightPx();
	std::cout << " " << units << std::endl;
}