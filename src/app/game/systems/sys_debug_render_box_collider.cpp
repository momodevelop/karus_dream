#include "sys_debug_render_box_collider.h"

#include "../components/com_transform.h"
#include "../components/com_box_collider.h"

namespace app::game::systems {
	using namespace components;

	void SysDebugRenderBoxCollider::render(entt::registry & ecs, SDL_Renderer & renderer)
	{
		SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);
		auto view = ecs.view<ComTransform, ComBoxCollider>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& bc = view.get<ComBoxCollider>(entity); 
			
			// top
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.x),
				int(transform.position.y + bc.box.y),
				int(transform.position.x + bc.box.x + bc.box.w),
				int(transform.position.y + bc.box.y)
			);

			// bottom
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.x),
				int(transform.position.y + bc.box.y + bc.box.h),
				int(transform.position.x + bc.box.x + bc.box.w),
				int(transform.position.y + bc.box.y + bc.box.h)
			);

			// left
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.x),
				int(transform.position.y + bc.box.y),
				int(transform.position.x + bc.box.x),
				int(transform.position.y + bc.box.y + bc.box.h)
			);

			// right
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.x + bc.box.w),
				int(transform.position.y + bc.box.y),
				int(transform.position.x + bc.box.x + bc.box.w),
				int(transform.position.y + bc.box.y + bc.box.h)
			);

		}
		
	}
}