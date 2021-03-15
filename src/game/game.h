#pragma once

#include <memory>
#include <stdint.h>

#include "engine/base/opengl_support.h"
#include "engine/base/singleton.h"

namespace urus 
{
	class ShaderProgram;

#if !defined(NDEBUG)
	class ConsoleView;
#endif // NDEBUG
	class Texture;
	class GameView;

	class Game : public Singleton<Game>
	{
		public:           
			virtual ~Game();            

			virtual bool setup(int argc, char* argv[]);
			virtual void shutdown();
			virtual void run(); // FIXME: needs to be public?

			inline std::shared_ptr<GameView> gameView() const { return mGameView;  }
			inline void setGameView(std::shared_ptr<GameView> gameView) { mGameView = gameView;  }
			void updateViewPositionAndBounds() const;
			void logScreenInfo() const;

			// FIXME: shouldn't the glut callbacks be ideally private?
			void animate();
			void visible(int isVisible);

		protected:
			Game();
			friend class Singleton<Game>;

			// Walkaround for OpenGL (c api) to accept callbacks to c++:
			// must use static methods, otherwise this pointer will screw up
			// the compilation, since the signatures will not match
			static void idle();
			static void render();
			static void keyboardCallback(unsigned char key, int x, int y);
			static void mouseCallback(int button, int state, int x, int y);
			static void mouseWheelCallback(int wheel, int direction, int x, int y);			
			static void reshape(int width, int height);
			
		protected:

			static constexpr GLuint NB_SHADERS = 2;
			static GLuint VBO;
			static GLuint VAO;
			static Texture* sTexture; // don't care if it is a raw pointer, since it is static anyway
			static std::unique_ptr<ShaderProgram> shaders[NB_SHADERS];
			
			std::shared_ptr<GameView> mGameView;

#if !defined(NDEBUG)
		public:
			inline void setConsoleView(std::shared_ptr<ConsoleView> consoleView) { mConsoleView = consoleView; }
		protected:
			std::shared_ptr<ConsoleView> mConsoleView;
#endif // NDEBUG
	}; // class Game
} // namespace urus
