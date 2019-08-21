#include "sys_player_collide_obstacle.h"

#include "../components/com_player.h"
#include "../components/com_obstacle.h"

namespace app::game::systems {
	using namespace components;
	void SysPlayerCollideObstacle::update(entt::registry & ecs)
	{
		auto obstacle = ecs.view<ComObstacle>();
		auto player = ecs.view<ComPlayer>();

		for (auto obstacle : view) {
			auto& player = view.get<ComPlayer>(entity);
			auto& obstacle = view.get<ComObstacle>(entity);


		}
	}
}`