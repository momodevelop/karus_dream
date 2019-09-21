#ifndef _APP_GAME_SHARED_SPAWNER_H__
#define _APP_GAME_SHARED_SPAWNER_H__

#include <entt.h>
#include <ryoji/vector.h>
#include "../shared/shared_animation_indices.h"

namespace app::game::shared {
	class SharedSpawner {
		enum EnemyType {
			GHOST,
			SKELETON,
			FROG,
			BAT,
		};
		float coinTimer;
		float coinDuration;
		entt::registry& ecs;
		shared::SharedAnimationIndices& animationIndices;

		void spawnCoin();
		void spawnEnemy(ryoji::math::Vec2f pos, bool facingRight, EnemyType type);
	public:
		SharedSpawner(entt::registry& ecs, shared::SharedAnimationIndices& animationIndices);
		~SharedSpawner();

		void update(float dt);

	};
}

#endif 