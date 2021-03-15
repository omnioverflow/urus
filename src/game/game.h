#pragma once

#include <memory>
#include <stdint.h>

#include "engine/base/opengl_support.h"
#include "engine/base/singleton.h"

namespace urus 
{
	class ShaderProgram;

#ifndef NDEBUG
	class ConsoleView;
#endif
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
			static void animate();
			static void reshape(int width, int height);
			static void visible(int isVisible);

		protected:

			static constexpr GLuint NB_SHADERS = 2;
			static GLuint VBO;
			static GLuint VAO;
			static Texture* sTexture; // don't care if it is a raw pointer, since it is static anyway
			static std::unique_ptr<ShaderProgram> shaders[NB_SHADERS];
			
			std::shared_ptr<GameView> mGameView;

#ifndef NDEBUG
		public:
			inline void setConsoleView(std::shared_ptr<ConsoleView> consoleView) { mConsoleView = consoleView; }
		protected:
			std::shared_ptr<ConsoleView> mConsoleView;
#endif
	}; // class Game
} // namespace urus
