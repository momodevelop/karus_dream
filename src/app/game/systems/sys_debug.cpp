#include <entt.h>
#include <SDL.h>

#include "sys_debug.h"

#include "../components/com_transform.h"
#include "../components/com_box_collider.h"



namespace app::game::systems {
	using namespace components;

	void SysDebug::renderBoxColliders(entt::registry & ecs, SDL_Renderer & renderer)
	{
		
		auto view = ecs.view<ComTransform, ComBoxCollider>();
		for (auto entity : view) {
			auto& transform = view.get<ComTransform>(entity);
			auto& bc = view.get<ComBoxCollider>(entity); 
			
			SDL_SetRenderDrawColor(&renderer, 0, 255, 0, 255);

			// top
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.min[0]),
				int(transform.position.y + bc.box.min[1]),
				int(transform.position.x + bc.box.max[0]),
				int(transform.position.y + bc.box.min[1])
			);

			// bottom
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.min[0]),
				int(transform.position.y + bc.box.max[1]),
				int(transform.position.x + bc.box.max[0]),
				int(transform.position.y + bc.box.max[1])
			);

			// left
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.min[0]),
				int(transform.position.y + bc.box.min[1]),
				int(transform.position.x + bc.box.min[0]),
				int(transform.position.y + bc.box.max[1])
			);

			// right
			SDL_RenderDrawLine(&renderer,
				int(transform.position.x + bc.box.max[0]),
				int(transform.position.y + bc.box.min[1]),
				int(transform.position.x + bc.box.max[0]),
				int(transform.position.y + bc.box.max[1])
			);

		}
		
	}

}
