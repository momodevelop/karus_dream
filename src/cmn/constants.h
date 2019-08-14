#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include "SDL.h"

constexpr static int gDisplayWidth = 800;
constexpr static int gDisplayHeight = 600;
constexpr static int gDisplayHalfWidth = gDisplayWidth / 2;
constexpr static int gDisplayHalfHeight = gDisplayHeight / 2;

struct SDLWindowDestroyer
{
	void operator()(SDL_Window* w) const
	{
		SDL_DestroyWindow(w);
	}
};

namespace app {

	constexpr static int kTileSize = 96;

	namespace character {

		enum AnimeDirection { ANIME_FRONT, ANIME_LEFT, ANIME_RIGHT, ANIME_BACK, ANIME_MAX };
		constexpr static uint8_t kAnimeMaxFrames = 4;
		constexpr static uint8_t kAnimeIndices[ANIME_MAX][kAnimeMaxFrames]{
			{ 1, 0, 1, 2 },
			{ 4, 3, 4, 5 },
			{ 7, 6, 7, 8 },
			{ 10, 9, 10, 11 }
		};

		constexpr static float kMoveAnimeDuration = 0.25f;
		constexpr static float kAnimeSpeed = 10.f;
		constexpr static int kSize = kTileSize;
		constexpr static int kHalfSize = kSize / 2;
	}

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