#include <cassert>
#include <ryoji/rect.h>
#include <ryoji/aabb.h>
#include <yuu/utils.h>

#include "sys_animator.h"
#include "../components/com_renderable.h"
#include "../components/com_animation.h"


namespace app::game::systems {
	using namespace components;
	using namespace yuu;
	void SysAnimator::update(entt::registry& registry, shared::SharedTextures& sharedTextures, float dt) {
		auto view = registry.view<ComAnimation, ComRenderable>();
		for (auto entity : view) 
		{
			auto& renderable = view.get<ComRenderable>(entity);
			auto& animation = view.get<ComAnimation>(entity);

			int index = (int)(animation.timer * animation.speed) % animation.indices.size();
			auto& textureData = sharedTextures[renderable.textureHandler];

			renderable.srcRect = getSubRect(
				SDL_Rect{ 0, 0, textureData.width, textureData.height }, 
				textureData.cols, 
				textureData.rows,
				animation.indices[index]);

			animation.timer += dt;
		}
	}
}