#ifndef __APP_GAME_SYSTEMS_PHYSICS_H__
#define __APP_GAME_SYSTEMS_PHYSICS_H__



namespace app::game::systems {
	class SysPhysics {
	public:
		static void updateConstantForces(entt::registry& ecs);
		static void updateMovement(entt::registry& ecs, float dt);
	};
}

#endif