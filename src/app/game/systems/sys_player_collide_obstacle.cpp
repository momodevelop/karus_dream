#include "sys_player_collide_obstacle.h"

#include "../components/com_player.h"
#include "../components/com_obstacle.h"
#include "../components/com_box_collider.h"

namespace app::game::systems {
	using namespace components;
	void SysPlayerCollideObstacle::update(entt::registry & ecs)
	{
		auto obstacles = ecs.view<ComBoxCollider, ComObstacle>();
		auto players = ecs.view<ComBoxCollider, ComPlayer>();

		for (auto obstacle : obstacles) {
			for (auto player : players) {
				auto& obstacleBox = obstacles.get<ComBoxCollider>(obstacle);
				auto& playerBox = players.get<ComBoxCollider>(player);
			

			}

		}
	}
}