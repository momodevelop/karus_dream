#ifndef __APP_GAME_SYSTEMS_PHYSICS_H__
#define __APP_GAME_SYSTEMS_PHYSICS_H__

#include <entt.h>

namespace app::game::systems {
	class SysPhysics {
	public:
		static void update(entt::registry& ecs, float dt);
	};
}

#endif