
#include <entt.h>

#include "../components/com_enemy.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"

#include "sys_ai.h"
#include <constants.h>
#include <ryoji/easing.h>


#define GROUND_AI_SPEED 25.f
#define FLYING_AI_SPEED 10.f
#define DEATH_SPEED 500.f

namespace app::game::systems {
	using namespace components;

	void SysAi::updateEnemyAi(entt::registry & ecs, float dt)
	{
		auto view = ecs.view<ComTransform, ComEnemy, ComRenderable>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& enemy = view.get<ComEnemy>(entity);
			auto& renderable = view.get<ComRenderable>(entity);

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
			case ComEnemy::STATE_DIE:
				transform.position.y += DEATH_SPEED * dt;
				transform.flipState = SDL_RendererFlip(transform.flipState | SDL_FLIP_VERTICAL);
				if (transform.position.y > gDisplayHeight) // hacky way to despawn
				{
					ecs.destroy(entity);
				}
				break;
			}
			
		}
	}

}