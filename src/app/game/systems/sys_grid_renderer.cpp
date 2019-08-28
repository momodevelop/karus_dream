#include <constants.h>
#include <yuu/utils.h>

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
				auto& textureData = sharedTextures[SharedTextures::GRID_SPRITESHEET];

				SDL_Rect srcRect = yuu::getSubRect(
					SDL_Rect{ 0, 0, textureData.width, textureData.height },
					textureData.cols,
					textureData.rows,
					sharedGrid.at(x,y).value);


				SDL_RenderCopy(&renderer, textureData.texture.get(), &srcRect, &destRect);
			}
		}
	}
}