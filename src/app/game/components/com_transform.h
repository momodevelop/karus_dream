#ifndef __APP_GAME_COMPONENTS_TRANSFORM_H__
#define __APP_GAME_COMPONENTS_TRANSFORM_H__

#include <ryoji/vector.h>
#include <SDL.h>

namespace app::game::components {
	struct ComTransform {
		ryoji::math::Vec2f position{};
		ryoji::math::Vec2f scale{};
		float rotation{};
		SDL_RendererFlip flipState { SDL_FLIP_NONE };
	};
}

#endif