#pragma once

#include <memory>
#include <stdint.h>

#include "engine/base/singleton.h"

namespace urus 
{
#ifndef NDEBUG
	class Console;
#endif
	class Window;

	class Application : public Singleton<Application>
	{
		public:           
			virtual ~Application();            

			virtual bool setup(int argc, char* argv[]);
			virtual void shutdown();
			virtual void run(); // FIXME: needs to be public?

			std::shared_ptr<Window> window() const { return mWindow;  }
			void setWindow(std::shared_ptr<Window> window) { mWindow = window;  }
			void updateWindowPositionAndBounds() const;

		protected:
			Application() = default;
			friend class Singleton<Application>;

			// Walkaround for OpenGL (c api) to accept callbacks to c++:
			// must use static methods, otherwise this pointer will screw up
			// the compilation, since the signatures will not match
			static void render();
			static void keyboardCallback(unsigned char key, int x, int y);
			static void mouseCallback(int button, int state, int x, int y);
			static void mouseWheelCallback(int wheel, int direction, int x, int y);
			static void animate();
			static void reshape(int width, int height);
			static void visible(int vis);

		protected:
			std::shared_ptr<Window> mWindow; // main window

#ifndef NDEBUG
		public:
			void setConsole(std::shared_ptr<Console> console) { mConsole = console;  }
		protected:
			std::shared_ptr<Console> mConsole;
#endif
	}; // class Application
} // namespace urus
