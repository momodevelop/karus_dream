#ifndef __APP_GAME_SYSTEMS_INPUT_H__
#define __APP_GAME_SYSTEMS_INPUT_H__

#include <entt.h>
#include <SDL.h>
#include "../shared/shared_keyboard.h"

namespace app::game::systems {
	class SysPlayerInput {
	public:
		void update(entt::registry& registry, shared::SharedKeyboard& sharedKeyboard, float dt);
	};


}

#endif