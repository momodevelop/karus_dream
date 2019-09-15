#ifndef __APP_GAME_TYPES_H__
#define __APP_GAME_TYPES_H__

#include <yuu/utils.h>

namespace app::game {
	enum TextureHandler {
		KARU_SPRITESHEET,
		GRID_SPRITESHEET,
		COIN_SPRITESHEET,

		ZERO, ONE, TWO, THREE, FOUR,
		FIVE, SIX, SEVEN, EIGHT, NINE,
		TEXT_SCORE,

		MAX
	};
}

#endif