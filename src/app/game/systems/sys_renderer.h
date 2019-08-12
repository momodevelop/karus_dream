#ifndef __APP_GAME_SYSTEMS_RENDERER_H__
#define __APP_GAME_SYSTEMS_RENDERER_H__

#include <SDL.h>
#include <entt.h>

namespace app::game::systems {
	class SysRenderer {
	public:
		static void render(entt::registry& registry, SDL_Renderer& renderer);
	};
}

#endif