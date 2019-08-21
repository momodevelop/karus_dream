#ifndef __APP_GAME_SYSTEMS_BOX_COLLISION_H__
#define __APP_GAME_SYSTEMS_BOX_COLLISION_H__

#include <entt.h>

namespace app::game::systems {
	class SysCollider {
	public:
		void update(entt::registry& ecs);
	};
}

#endif