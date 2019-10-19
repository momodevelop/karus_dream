#ifndef __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__
#define __APP_GAME_SYSTEMS_DEBUG_RENDER_BOX_COLLIDER_H__


namespace app::game::systems {
	class SysDebug {
	public:
		static void renderBoxColliders(entt::registry& ecs, SDL_Renderer& renderer);
	};
}

#endif