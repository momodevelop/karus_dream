#ifndef __APP_GAME_TYPES_H__
#define __APP_GAME_TYPES_H__

#include <yuu/utils.h>

namespace app::game {
	enum TextureHandler {
		TEXTURE_KARU_SPRITESHEET,
		TEXTURE_GRID_SPRITESHEET,
		TEXTURE_MAX
	};

	using texture_resources_t = std::array<yuu::SDL_TextureUniquePtr, TEXTURE_MAX>;
}

#endif