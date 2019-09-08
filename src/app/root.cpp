#include <yuu/time.h>
#include <constants.h>
#include <SDL.h>


#include "root.h"
#include "splash/state.h"
#include "game/state.h"
#include "menu/state.h"

namespace app {
	
	using namespace yuu;

	Root::Root(SDL_Window& window, yuu::Time& time) :
		window(window), time(time),
		currentState(STATE_NONE), nextState(STATE_NONE)
	{
	}

	Root::~Root() noexcept {

	}


	void Root::run() {

		// tick once first to start the timer
		time.tick(); 

		// Initialize state
		state = createState(STATE_SPLASH);
		currentState = nextState = STATE_SPLASH;


		// Game Loop
		while (state) {
			time.tick();
			this->handleEvents();
			this->update();
			this->render();
			this->clean();
			SDL_Delay(10);
		}
	}



	void Root::render() {
		auto& renderer = (*SDL_GetRenderer(&window));
		SDL_RenderClear(&renderer);
		state->onRender(renderer);
		SDL_RenderPresent(&renderer);
	}

	void Root::handleEvents() {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				nextState = STATE_EXIT;
			}
			state->onHandleEvent(e);
		}
		
	}

	void Root::clean() 
	{
		state->onClean();
	
		// check for state switch
		if (currentState != nextState) {
			if (state) {
				state->onExit();
			}
		
			state.reset();
			state = createState(nextState);

			if (state)
				state->onEnter();

			currentState = nextState;


		}
	}

	void Root::update() {
		state->onUpdate(time.getTimeElpased<float>());
	}


	std::unique_ptr<StateBase> Root::createState(StateEnum e)
	{
		StateBase * ret = nullptr;
		auto& renderer = *SDL_GetRenderer(&window);
		switch (e)
		{
		case STATE_SPLASH:
			return std::make_unique<splash::State>(renderer, [=](){
				nextState = STATE_MENU;
			});
			break;
		case STATE_MENU:
			return std::make_unique<menu::State>(renderer,
				[=]() {	nextState = STATE_GAME; },
				[=]() { nextState = STATE_EXIT; }			
			);
			break;
		case STATE_GAME:
			return std::make_unique<game::State>(renderer);
			break;
		default:
			break;
		}
		
		return nullptr;
	}

}