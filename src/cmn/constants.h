#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <array>

constexpr static int gDisplayWidth = 800;
constexpr static int gDisplayHeight = 600;
constexpr static int gDisplayHalfWidth = gDisplayWidth / 2;
constexpr static int gDisplayHalfHeight = gDisplayHeight / 2;

namespace character {

	namespace animation {
		enum Direction { FRONT, LEFT, RIGHT, BACK, MAX };
		constexpr static uint8_t kMaxFrames = 4;
		constexpr static std::array<std::array<uint8_t, kMaxFrames>, MAX> kIndicesSet = {
			std::array<uint8_t, kMaxFrames>{ 1, 0, 1, 2 },
			std::array<uint8_t, kMaxFrames>{ 4, 3, 4, 5 },
			std::array<uint8_t, kMaxFrames>{ 7, 6, 7, 8 },
			std::array<uint8_t, kMaxFrames>{ 10, 9, 10, 11 }
		};
		constexpr static float kSpeed = 10.f;
	}
	constexpr static float kMoveSpeed = 500.f;
	constexpr static int kSize = 48;
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