#ifndef __APP_GAME_SYSTEMS_RENDERER_H__
#define __APP_GAME_SYSTEMS_RENDERER_H__

#include <SDL.h>
#include <entt.h>
#include <yuu/utils.h>
#include "../types.h"

namespace app::game::systems {
	class SysRenderer {
	public:
		static void render(entt::registry& registry, SDL_Renderer& renderer, texture_resources_t& textures);
	};
}

#endif