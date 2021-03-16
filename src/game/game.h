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
	class GameView;
	class GameWorld;
	class Texture;

	class Game : public Singleton<Game>
	{
		public:    
			virtual ~Game();            

			virtual bool setup(int argc, char* argv[]);
			virtual void shutdown();
			virtual int run(); // FIXME: needs to be public?

			GameView& gameView() const;
			void setGameView(std::unique_ptr<GameView> gameView);
			GameWorld& gameWorld() const;
			void setGameWorld(std::unique_ptr<GameWorld> gameWorld);

			void updateViewPositionAndBounds() const;
			void logScreenInfo() const;

			// FIXME: shouldn't the glut callbacks be ideally private?
			void animate();
			void visible(int isVisible);

		protected:
			Game();
			friend class Singleton<Game>;

			// Workaround for OpenGL (c api) to accept callbacks to c++:
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
			
			std::unique_ptr<GameView> mGameView;
			std::unique_ptr<GameWorld> mGameWorld;

#if !defined(NDEBUG)
		public:
			void setConsoleView(std::unique_ptr<ConsoleView> consoleView);
		protected:
			std::unique_ptr<ConsoleView> mConsoleView;
#endif // NDEBUG
	}; // class Game
} // namespace urus
