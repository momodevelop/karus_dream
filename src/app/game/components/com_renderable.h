#ifndef __APP_GAME_COMPONENTS_RENDERABLE_H__
#define __APP_GAME_COMPONENTS_RENDERABLE_H__

#include <SDL.h>
#include "../shared/shared_textures.h"

namespace app::game::components {
	struct ComRenderable {
		SDL_Rect srcRect = { 0, 0, 0, 0 };
		shared::SharedTextures::Handler textureHandler = {};
		Uint8 alpha = Uint8(-1);
	};
}


#endif