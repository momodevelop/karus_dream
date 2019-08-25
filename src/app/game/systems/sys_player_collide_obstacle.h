#ifndef __APP_GAME_SYSTEMS_PLAYER_COLLIDE_OBSTACLE_H__
#define __APP_GAME_SYSTEMS_PLAYER_COLLIDE_OBSTACLE_H__

#include <SDL.h>
#include <entt.h>
#include <ryoji/rect.h>

namespace app::game::systems {
	class SysPlayerCollideObstacle
	{
	public:
		void update(entt::registry& ecs);
	};
}

#endif 
