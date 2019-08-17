#ifndef __APP_GAME_SYSTEMS_INPUT_H__
#define __APP_GAME_SYSTEMS_INPUT_H__

#include <entt.h>
#include <SDL.h>

namespace app::game::systems {
	class SysPlayerInput {
		void handleKeyDown();
		void handleKeyUp();
	public:
		void handleEvent(entt::registry& registry, SDL_Event& e);
	};

}

#endif