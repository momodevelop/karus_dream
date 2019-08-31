#include "shared_textures.h"

#include <ryoji/common.h>
using namespace ryoji;
using namespace yuu;

namespace app::game::shared {
/*
	bool SharedTextures::initTextureData(SDL_Renderer& renderer, SharedTextures::Handler handler, const char * path, int width, int height, int rows, int cols) {
		textures[handler] = TextureData{
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, path)),
			handler,
			width, height, 
			rows, cols,
		};
		if (!textures[handler].texture)
			return false;

		// generate the SDL_Rects
		int tileWidth = width / cols;
		int tileHeight = height / rows;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				auto index = math::get1dFrom2d(j, i, cols);
				frames[handler].emplace_back(SDL_Rect{
					j * tileWidth,
					i * tileHeight,
					tileWidth,
					tileHeight
				});
			}
		}
		


		return true;
	}

	bool SharedTextures::init(SDL_Renderer& renderer)
	{
		return 
			initTextureData(renderer, KARU_SPRITESHEET, "img/spritesheet_karu.png", 144, 192, 4, 3) &&
			initTextureData(renderer, GRID_SPRITESHEET, "img/plains.png", 80, 48, 3, 5);

	}

	*/
}