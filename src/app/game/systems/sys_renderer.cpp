
#include "sys_renderer.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"


namespace app::game::systems {
	using namespace components;
	void SysRenderer::render(entt::registry& registry, SDL_Renderer& renderer)
	{
		auto view = registry.view<ComTransform, ComRenderable>();
		for (auto entity : view) {
			auto& renderable = view.get<ComRenderable>(entity);
			auto& transform = view.get<ComTransform>(entity);
			
			renderable.destRect = {
				(int)transform.position.x,
				(int)transform.position.y,
				(int)transform.scale.x,
				(int)transform.scale.y
			};

			SDL_SetTextureAlphaMod(renderable.texture, renderable.alpha);
			SDL_RenderCopy(&renderer, renderable.texture, &renderable.srcRect, &renderable.destRect);
		}

		
	}
}