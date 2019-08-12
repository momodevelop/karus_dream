#include <yuu/time.h>
#include <constants.h>

#include "root.h"


namespace app {
	
	using namespace yuu;

	Root::Root() :
		core("Sandbox", kDisplayWidth, kDisplayHeight),
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

	void Root::setNextState(StateEnum state)
	{
		nextState = state;
	}


	void Root::render() {
		SDL_RenderClear(&core.getRenderer());
		
		state->onRender(core.getRenderer());

		SDL_RenderPresent(&core.getRenderer());
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
				delete state;
			}
		
			state = createState(nextState);

			if (state)
				state->onEnter();

			currentState = nextState;


		}
	}

	void Root::update() {
		state->onUpdate(time.getTimeElpased<float>());
	}


	StateBase * Root::createState(StateEnum e)
	{
		StateBase * ret = nullptr;
		switch (e)
		{
		case STATE_SPLASH:
			ret = new StateSplash(core.getRenderer(), [=](){
				setNextState(Root::STATE_GAME);
			});
			break;
		case STATE_GAME:
			ret = new StateGame(core.getRenderer());
			break;
		default:
			break;
		}
		
		return ret;
	}

}