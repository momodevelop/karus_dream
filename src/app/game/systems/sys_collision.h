#ifndef __APP_GAME_SYSTEMS_PLAYER_COLLIDE_OBSTACLE_H__
#define __APP_GAME_SYSTEMS_PLAYER_COLLIDE_OBSTACLE_H__

#include <entt.h>


namespace app::game::systems {
	class SysCollision
	{
		static void syncBoxColliderToTransform(components::ComBoxCollider&, const components::ComTransform&);
	public:
		static void resolvePlayerJumpTriggerCollision(entt::registry& ecs, entt::entity player);
		static void resolvePlayerCollideCollectible(entt::registry& ecs, entt::entity player);
		static void resolvePlayerCollideObstacle(entt::registry& ecs, entt::entity player);
	};
}

#endif 
