#ifndef __APP_GAME_COMPONENTS_RENDERABLE_H__
#define __APP_GAME_COMPONENTS_RENDERABLE_H__

#include <SDL.h>
#include "../types.h"

namespace app::game::components {
	struct ComRenderable {
		SDL_Rect destRect = { 0, 0, 0, 0 };
		SDL_Rect srcRect = { 0, 0, 0, 0 };
		TextureHandler texture = {};
		Uint8 alpha = Uint8(-1);
	};
}


#endif