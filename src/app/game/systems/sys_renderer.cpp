#include <constants.h>
#include <yuu/utils.h>

#include "sys_renderer.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"


namespace app::game::systems {

	void SysRenderer::renderForeground(SDL_Renderer & renderer, shared::SharedTextures& textures)
	{
		auto& textureData = textures[TextureHandler::GRID_SPRITESHEET];

		float offset = gDisplayWidth / 20;
		for (float i = 0.f; i < gDisplayWidth; i += offset) {

			int k = 0;
			for (float j = gDisplayHalfHeight; j < gDisplayHeight; j += offset, ++k) {
				// top
				SDL_Rect destRect = {
					int(i),
					int(j),
					int(offset),
					int(offset)
				};
				int index = 11;
				if (k == 0)	index = 0;
				else if (k == 1) index = 6;

				SDL_SetTextureAlphaMod(textureData.texture.get(), 255);
				SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, index), &destRect);
			}


		}
	}
	void SysRenderer::renderBackground(SDL_Renderer & renderer, shared::SharedTextures& textures)
	{
		auto& textureData = textures[TextureHandler::GRID_SPRITESHEET];
		float offset = gDisplayWidth / 20;

		int ii = 0;
		for (float i = 0.f; i < gDisplayWidth; i += offset, ++ii) {
			int jj = 0;
			for (float j = 0.f; j < gDisplayHalfHeight; j += offset, ++jj) {

				SDL_Rect destRect = {
					int(i),
					int(j),
					int(offset),
					int(offset)
				};


				SDL_SetTextureAlphaMod(textureData.texture.get(), 255);
				if (jj == 4 )
					SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, 8), &destRect);
				else
					SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, 2), &destRect);
			}
		}

	}
	void SysRenderer::render(entt::registry& registry, SDL_Renderer& renderer, shared::SharedTextures& textures)
	{
		using namespace components;
		auto view = registry.view<ComTransform, ComRenderable>();
		for (auto entity : view) {
			auto& renderable = view.get<ComRenderable>(entity);
			auto& transform = view.get<ComTransform>(entity);
			
			SDL_Rect destRect = {
				(int)transform.position.x,
				(int)transform.position.y,
				(int)transform.scale.x,
				(int)transform.scale.y
			};

			auto texture = textures[renderable.textureHandler].texture.get();
			SDL_SetTextureAlphaMod(texture, renderable.alpha);
			SDL_RenderCopyEx(&renderer, texture, &renderable.srcRect, &destRect, (double)transform.rotation, nullptr, transform.flipState);
		}

		
	}
}