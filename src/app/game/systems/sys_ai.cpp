
#include <entt.h>

#include "../components/com_enemy.h"
#include "../components/com_transform.h"

#include "sys_ai.h"
#include <constants.h>


#define GROUND_AI_SPEED 25.f
#define FLYING_AI_SPEED 10.f

namespace app::game::systems {
	using namespace components;
	
	void SysAi::updateAiMovement(entt::registry & ecs, float dt)
	{
		auto view = ecs.view<ComTransform, ComEnemy>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& enemy = view.get<ComEnemy>(entity);

			enemy.entered = isWithinScreen(transform.position.x, transform.position.y);
			transform.position.x += GROUND_AI_SPEED * dt;

		}
	}

}