#include <constants.h>

#include "sys_grid_renderer.h"

namespace app::game::systems {
	using namespace shared;
	void SysGridRenderer::render(SDL_Renderer & renderer, SharedGrid & sharedGrid, SharedTextures & sharedTextures)
	{
		for (size_t y = 0; y < sharedGrid.getRows(); ++y) {
			for (size_t x = 0; x < sharedGrid.getColumns(); ++x) {
				SDL_Rect destRect = {
					(int)sharedGrid.getTilePosX(x),
					(int)sharedGrid.getTilePosY(y),
					(int)sharedGrid.getTileWidth(),
					(int)sharedGrid.getTileHeight()
				};
				SDL_Rect srcRect = {
					(int)sharedGrid.getTilePosX(x),
					(int)sharedGrid.getTilePosY(y),
					(int)sharedGrid.getTileWidth(),
					(int)sharedGrid.getTileHeight()
				};
				auto texture = sharedTextures[SharedTextures::GRID_SPRITESHEET].texture.get();

				SDL_RenderCopy(&renderer, texture, &srcRect, &destRect);
			}
		}
	}
}