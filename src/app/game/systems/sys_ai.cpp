
#include <entt.h>

#include "../components/com_enemy.h"
#include "../components/com_transform.h"

#include "sys_ai.h"



namespace app::game::systems {
	using namespace components;
	
	void SysAi::updateAiMovement(entt::registry & ecs, float dt)
	{
		auto view = ecs.view<ComTransform, ComEnemy>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& enemy = view.get<ComEnemy>(entity);

			
		}
	}

}