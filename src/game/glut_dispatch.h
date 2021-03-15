#pragma once

#include "game.h"

// Trampolines/thunks to dispatch callbacks from glut to static functions

extern "C" void dispatchAnimate()
{
    urus::Game::sharedInstance().animate();
}

extern "C" void dispatchVisible(int isVisible)
{
    urus::Game::sharedInstance().visible(isVisible);
}