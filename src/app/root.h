#ifndef __APP_ROOT_H__
#define __APP_ROOT_H__

#include <yuu/time.h>
#include <yuu/core.h>

#include "states/state_base.h"
#include "states/state_splash.h"
#include "states/state_game.h"


namespace app {


	class Root { 
	public:
		enum StateEnum : uint8_t {
			STATE_NONE,
			STATE_SPLASH,
			STATE_GAME,
			STATE_EXIT,
		};

	private:
		// important stuff
		yuu::Core core;
		yuu::Time time;
		
		//State
		StateBase* state;
		StateEnum currentState;
		StateEnum nextState;
		StateBase* createState(StateEnum e);

	public:
		Root();
		~Root() noexcept;

		void run();
		
		// For states
		void setNextState(StateEnum state);

	private:
		void update();
		void render();
		void handleEvents();
		void clean();
	};
}



#endif