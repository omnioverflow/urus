#pragma once

#include "game.h"

// Trampolines/thunks to dispatch callbacks from glut to static functions

namespace glut_dispatch
{
    extern "C" void displayFunc()
    {
        urus::Game::sharedInstance().render();
    }

    extern "C" void visibilityFunc(int isVisible)
    {
        urus::Game::sharedInstance().visible(isVisible);
    }

    extern "C" void reshapeFunc(int width, int height)
    {
        // FIXME: provide impl
    }

    extern "C" void keyboardFunc(unsigned char key, int x, int y)
    {
        // FIXME: provide impl
    }

    extern "C" void mouseFunc(int button, int state, int x, int y)
    {
        // FIXME: provide impl
    }

    extern "C" void mouseWheelFunc(int wheel, int direction, int x, int y)
    {
        // FIXME: provide impl
    }
    
    extern "C" void idleFunc()
    {
        // FIXME: provide impl
        urus::Game::sharedInstance().animate();
    }

} // namespace glut_dispatch