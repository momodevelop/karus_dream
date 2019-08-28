#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <array>

namespace spritesheets {
	namespace character {
		constexpr static int gCols = 3;
		constexpr static int gRows = 4;
		constexpr static int gWidth = 144;
		constexpr static int gHeight = 192;
		constexpr static int gTileWidth = gWidth / gCols;
		constexpr static int gTileHeight = gHeight / gRows;
	}
	namespace world {
		constexpr static int gCols = 4;
		constexpr static int gRows = 3;
		constexpr static int gWidth = 160;
		constexpr static int gHeight = 120;
		constexpr static int gTileWidth = gWidth / gCols;
		constexpr static int gTileHeight = gHeight / gRows;

	}
}



namespace character {
	constexpr static float gAnimeSpeed = 10.f;
	constexpr static float gMoveSpeed = 500.f;
	constexpr static int gSize = 96;
	constexpr static int gHalfSize = gSize / 2;
}


constexpr static int gDisplayWidth = 800;
constexpr static int gDisplayHeight = 600;
constexpr static int gDisplayHalfWidth = gDisplayWidth / 2;
constexpr static int gDisplayHalfHeight = gDisplayHeight / 2;

constexpr static int gTileSize = 48;



#endif