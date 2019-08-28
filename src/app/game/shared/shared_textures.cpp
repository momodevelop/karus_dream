#include "shared_textures.h"

using namespace yuu;

namespace app::game::shared {

	bool SharedTextures::initTextureData(SDL_Renderer& renderer, SharedTextures::Handler handler, const char * path, int width, int height, int rows, int cols) {
		textures[handler] = TextureData{
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, path)),
			handler,
			width, height, 
			rows, cols,
		};
		if (!textures[handler].texture)
			return false;
		return true;
	}

	bool SharedTextures::init(SDL_Renderer& renderer)
	{
		return 
			initTextureData(renderer, KARU_SPRITESHEET, "img/spritesheet_karu.png", 144, 192, 4, 3) &&
			initTextureData(renderer, GRID_SPRITESHEET, "img/tiles.jpg", 160, 120, 3, 4);

	}
}