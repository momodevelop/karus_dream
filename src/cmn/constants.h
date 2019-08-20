#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <array>

constexpr static int gDisplayWidth = 800;
constexpr static int gDisplayHeight = 600;
constexpr static int gDisplayHalfWidth = gDisplayWidth / 2;
constexpr static int gDisplayHalfHeight = gDisplayHeight / 2;

namespace character {

	constexpr static float kAnimeSpeed = 10.f;
	constexpr static float kMoveSpeed = 500.f;
	constexpr static int kSize = 96;
}

namespace app {

	constexpr static int kTileSize = 48;



	namespace grid {
		constexpr static int kSpritesheetC = 4;
		constexpr static int kSpritesheetR = 3;
		constexpr static int kSpritesheetTile = 40;
		constexpr static int kSpritesheetW = kSpritesheetTile * kSpritesheetC;
		constexpr static int kSpritesheetH = kSpritesheetTile * kSpritesheetR;
		constexpr static int kSize = kTileSize;
		constexpr static int kHalfSize = kSize / 2;
	}

}


#endif