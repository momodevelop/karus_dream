#ifndef __APP_STATE_BASE_H__
#define __APP_STATE_BASE_H__

#include <SDL.h>

namespace app {
	class StateBase {
	public:
		virtual ~StateBase() {}
		virtual void onEnter() {}
		virtual void onUpdate(float dt) {}
		virtual void onExit() {}
		virtual void onHandleEvent(SDL_Event& e) {}
		virtual void onRender(SDL_Renderer& renderer) {}
		virtual void onClean() {}
	};
}

#endif