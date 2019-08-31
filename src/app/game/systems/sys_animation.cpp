
#include <entt.h>
#include <ryoji/rect.h>
#include <ryoji/aabb.h>
#include <yuu/utils.h>
#include <yuu/texture_manager.h>

#include "../components/com_animation.h"
#include "../components/com_renderable.h"
#include "../components/com_character_animation.h"

#include "../shared/shared_textures.h"
#include "../shared/shared_character_animations.h"

#include "sys_animation.h"


namespace app::game::systems {
	using namespace components;
	using namespace yuu;
	void SysAnimation::updateCharacterAnimationType(entt::registry & registry, shared::SharedCharacterAnimations & characterAnimations)
	{
		auto view = registry.view<ComAnimation, ComCharacterAnimation>();
		for (auto entity : view) {
			auto& character = view.get<ComCharacterAnimation>(entity);
			auto& animation = view.get<ComAnimation>(entity);

			if (character.currentAnimeDir != character.nextAnimeDir) {
				using namespace character;
				auto& animIndex = characterAnimations[character.nextAnimeDir];
				animation.indices.assign(animIndex.cbegin(), animIndex.cend());
				character.currentAnimeDir = character.nextAnimeDir;
			}
		}
	}

	void SysAnimation::updateAnimation(entt::registry& registry, shared::SharedTextures& sharedTextures, float dt) {
		auto view = registry.view<ComAnimation, ComRenderable>();
		for (auto entity : view) 
		{
			auto& renderable = view.get<ComRenderable>(entity);
			auto& animation = view.get<ComAnimation>(entity);

			int index = (int)(animation.timer * animation.speed) % animation.indices.size();
			auto& textureData = sharedTextures[renderable.textureHandler];

			renderable.srcRect = sharedTextures.getFrame(renderable.textureHandler, animation.indices[index]);
			

			animation.timer += dt;
		}
	}
}