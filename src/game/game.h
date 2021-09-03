#pragma once

#include <memory>
#include <stdint.h>

#include "engine/base/OpenGLSupport.h"
#include "engine/base/Singleton.h"

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

			/**
			* Creates a GLUT view.
			* As part of the view creation the method does the following:
			* - initialize GLUT
			* - create OpenGL rendering context (RC)
			* - create GLUT window
			* - bind GLUT callback to specific methods of the Game class
			*/
			void createView(int argc, char* argv[]);
			void loadResources();
			void shutdown();
			int	 run(); 

			GameView& gameView() const;
			void setGameView(std::unique_ptr<GameView> gameView);
			GameWorld& gameWorld() const;
			void setGameWorld(std::unique_ptr<GameWorld> gameWorld);

			void updateViewPositionAndBounds() const;

			// FIXME: shouldn't the glut callbacks be ideally private?
			void animate();
			void render();
			void visible(int isVisible);

#if !defined(NDEBUG)			
			void setConsoleView(std::unique_ptr<ConsoleView> consoleView);
#endif // NDEBUG

		protected:
			Game();
			friend class Singleton<Game>;

			// Workaround for OpenGL (c api) to accept callbacks to c++:
			// must use static methods, otherwise this pointer will screw up
			// the compilation, since the signatures will not match
			static void idle();
			static void keyboardCallback(unsigned char key, int x, int y);
			static void mouseCallback(int button, int state, int x, int y);
			static void mouseWheelCallback(int wheel, int direction, int x, int y);			
			static void reshape(int width, int height);		

			static constexpr GLuint NB_SHADERS = 2;
			static GLuint VBO;
			static GLuint VAO;
			static Texture* sTexture; // don't care if it is a raw pointer, since it is static anyway
			static std::unique_ptr<ShaderProgram> shaders[NB_SHADERS];
			
			std::unique_ptr<GameView> mGameView;
			std::unique_ptr<GameWorld> mGameWorld;

#if !defined(NDEBUG)		
			std::unique_ptr<ConsoleView> mConsoleView;
#endif // NDEBUG

		private:

			class GlutDispatcher
			{
				public:

					static void displayFunc();
					static void idleFunc();
					static void keyboardFunc(unsigned char key, int x, int y);
					static void mouseFunc(int button, int state, int x, int y);
					static void mouseWheelFunc(int wheel, int direction, int x, int y);					
					static void reshapeFunc(int width, int height);
					static void visibilityFunc(int isVisible);									
			}; // class GlutDispatcher
	}; // class Game
} // namespace urus
