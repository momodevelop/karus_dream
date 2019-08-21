#ifndef __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__
#define __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__

#include <entt.h>
#include <SDL.h>

namespace app::game::systems {
	class SysDebugRenderBoxCollider {
	public:
		void render(entt::registry& ecs, SDL_Renderer& renderer);
	};
}

#endif