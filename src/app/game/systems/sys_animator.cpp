#include <cassert>
#include <ryoji/rect.h>
#include <ryoji/aabb.h>

#include "sys_animator.h"
#include "../components/com_renderable.h"
#include "../components/com_animation.h"


namespace app::game::systems {
	using namespace components;

	SDL_Rect SysAnimator::getSubRect(SDL_Rect rect, int c, int r, int index) {
		return SDL_Rect{
			(index % c) * (rect.w - rect.x) / c,
			(index / c) * (rect.h - rect.y) / r,
			(rect.w - rect.x) / c,
			(rect.h - rect.y) / r
		};
	}

	void SysAnimator::update(entt::registry& registry, float dt) {
		auto view = registry.view<ComAnimation, ComRenderable>();
		for (auto entity : view) 
		{
			auto& renderable = view.get<ComRenderable>(entity);
			auto& animation = view.get<ComAnimation>(entity);

			int index = (int)(animation.timer * animation.speed) % animation.indices.size();
			renderable.srcRect = getSubRect(SDL_Rect{ 0, 0, kSpritesheetW, kSpritesheetH }, kSpritesheetC, kSpritesheetR, animation.indices[index]);
			animation.timer += dt;
		}
	}
}