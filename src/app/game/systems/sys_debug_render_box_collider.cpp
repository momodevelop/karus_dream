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
				int(transform.position.x + bc.box.minX),
				int(transform.position.y + bc.box.minY),
				int(transform.position.x + bc.box.maxY),
				int(transform.position.y + bc.box.minY)
			);

			// bottom
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.minX),
				int(transform.position.y + bc.box.maxY),
				int(transform.position.x + bc.box.maxX),
				int(transform.position.y + bc.box.maxY)
			);

			// left
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.minX),
				int(transform.position.y + bc.box.minY),
				int(transform.position.x + bc.box.minX),
				int(transform.position.y + bc.box.maxY)
			);

			// right
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.maxX),
				int(transform.position.y + bc.box.minY),
				int(transform.position.x + bc.box.maxX),
				int(transform.position.y + bc.box.maxY)
			);
			
		}
		
	}
}