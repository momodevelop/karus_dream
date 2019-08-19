#include <constants.h>

#include "sys_character_animator.h"
#include "../components/com_character_animation.h"
#include "../components/com_animation.h"

namespace app::game::systems {

	using namespace ryoji::math;
	using namespace components;

	void SysCharacterAnimator::update(entt::registry& registry) {
		auto view = registry.view<ComAnimation, ComCharacterAnimation>();
		for (auto entity : view) {
			auto& character = view.get<ComCharacterAnimation>(entity);
			auto& animation = view.get<ComAnimation>(entity);

			if (character.currentAnimeDir != character.nextAnimeDir) {
				using namespace character::animation;
				auto animIndex = kIndicesSet[character.nextAnimeDir];
				animation.indices.assign(animIndex.cbegin(), animIndex.cend());
				character.currentAnimeDir = character.nextAnimeDir;
			}


		}
	}
}