
#include <entt.h>

#include "../components/com_enemy.h"
#include "../components/com_transform.h"

#include "sys_ai.h"
#include <constants.h>


#define GROUND_AI_SPEED 25.f
#define FLYING_AI_SPEED 10.f

namespace app::game::systems {
	using namespace components;
	
	void SysAi::updateAiDamageTakeCooldown(entt::registry & ecs, float dt)
	{
	}

	void SysAi::updateAiMovement(entt::registry & ecs, float dt)
	{
		auto view = ecs.view<ComTransform, ComEnemy>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& enemy = view.get<ComEnemy>(entity);

			switch (enemy.state) {
			case ComEnemy::STATE_MOVING_LEFT:
				transform.position.x -= GROUND_AI_SPEED * dt;
				if (transform.position.x < 0) {
					enemy.state = ComEnemy::STATE_MOVING_RIGHT;
					transform.flipState = SDL_FLIP_NONE;
				}
				break;
			case ComEnemy::STATE_MOVING_RIGHT:
				transform.position.x += GROUND_AI_SPEED * dt;
				if (transform.position.x >= gDisplayWidth - transform.scale.x) {
					enemy.state = ComEnemy::STATE_MOVING_LEFT;
					transform.flipState = SDL_FLIP_HORIZONTAL;
				}
				break;
			}
			
		}
	}

	void SysAi::updateAiDeath(entt::registry & ecs, float dt)
	{
	}

}