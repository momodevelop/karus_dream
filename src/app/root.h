#ifndef __APP_ROOT_H__
#define __APP_ROOT_H__

#include <SDL.h>
#include <yuu/time.h>
#include <yuu/core.h>

#include "states/state_base.h"
#include "states/state_splash.h"
#include "states/state_game.h"


namespace app {
	// Responsibility: Manages the different states
	class Root {
	public:
		enum StateEnum : uint8_t {
			STATE_NONE,
			STATE_SPLASH,
			STATE_GAME,
			STATE_EXIT,
		};

	private:
		std::unique_ptr<SDL_Window> window;
		yuu::Time& time;
		
		//State
		std::unique_ptr<StateBase> state;
		StateEnum currentState;
		StateEnum nextState;
		std::unique_ptr<StateBase> createState(StateEnum e);

	public:
		Root(std::unique_ptr<SDL_Window> window, yuu::Time& time);
		~Root() noexcept;

		void run();

	private:
		void update();
		void render();
		void handleEvents();
		void clean();
	};
}



#endif