#ifndef __APP_ROOT_H__
#define __APP_ROOT_H__

#include <functional>
#include <yuu/time.h>
#include "types.h"
#include "state_base.h"

namespace app {
	class Root {
		SDL_Window& window;
		yuu::Time& time;
		
		//State
		std::unique_ptr<StateBase> state;
		StateEnum currentState;
		StateEnum nextState;
		std::unique_ptr<StateBase> createState(StateEnum e);

	public:
		Root(SDL_Window& window, yuu::Time& time);
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