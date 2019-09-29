#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <SDL.h>
#include <array>


namespace character {
	constexpr static float gAnimeSpeed = 10.f;
	constexpr static float gMoveSpeed = 200.f;
	constexpr static float gJump = 650.f;
}

constexpr static int gDisplayWidth = 800;
constexpr static int gDisplayHeight = 400;
constexpr static int gDisplayHalfWidth = gDisplayWidth / 2;
constexpr static int gDisplayHalfHeight = gDisplayHeight / 2;
constexpr static int gTileSize = 48;
constexpr static int gHalfTileSize = gTileSize/2;
constexpr static float gFloorY = float(gDisplayHalfHeight);
constexpr static float gSpawnableHeight = float(gDisplayHalfHeight - gTileSize);
constexpr static float gJumpTriggerSize = 1.f;
constexpr static float gWeaponTriggerWidth = 48.f;
constexpr static float gWeaponTriggerHeight = 24.f;
constexpr static int gEnemySize = 24;

inline bool isWithinScreen(int x, int y) {
	return x >= 0 && x < gDisplayWidth && y >= 0 && y < gDisplayHeight;
}


#endif