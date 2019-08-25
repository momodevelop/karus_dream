#ifndef __APP_GAME_SYSTEMS_ANIMATOR_H__
#define __APP_GAME_SYSTEMS_ANIMATOR_H__

#include <SDL.h>
#include <entt.h>

namespace app::game::systems {

	class SysAnimator {
		inline constexpr static std::uint8_t kSpritesheetC = 3;
		inline constexpr static std::uint8_t kSpritesheetR = 4;
		inline constexpr static std::uint8_t kSpritesheetTileSize = 48;
		inline constexpr static std::uint8_t kSpritesheetW = kSpritesheetC * kSpritesheetTileSize;
		inline constexpr static std::uint8_t kSpritesheetH = kSpritesheetR * kSpritesheetTileSize;

		SDL_Rect getSubRect(SDL_Rect rect, int c, int r, int index);
	public:
		void update(entt::registry& registry, float dt);
	};
}


#endif