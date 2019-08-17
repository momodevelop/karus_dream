
#include "sys_renderer.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"


namespace app::game::systems {
	using namespace components;
	void SysRenderer::render(entt::registry& registry, SDL_Renderer& renderer, shared::SharedTextures& textures)
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

			auto texture = textures[renderable.texture].get();
			SDL_SetTextureAlphaMod(texture, renderable.alpha);
			SDL_RenderCopy(&renderer, texture, &renderable.srcRect, &renderable.destRect);
		}

		
	}
}