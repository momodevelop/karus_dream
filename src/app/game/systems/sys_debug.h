#ifndef __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__
#define __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__


#ifdef _DEBUG

namespace app::game::systems {
	class SysDebug {
	public:
		static void renderBoxColliders(entt::registry& ecs, SDL_Renderer& renderer);
	};
}

#endif
#endif