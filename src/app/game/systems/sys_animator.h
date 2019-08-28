#ifndef __APP_GAME_SYSTEMS_ANIMATOR_H__
#define __APP_GAME_SYSTEMS_ANIMATOR_H__

#include <SDL.h>
#include <entt.h>
#include "../shared/shared_textures.h"

namespace app::game::systems {

	class SysAnimator {
		inline constexpr static std::uint8_t kSpritesheetC = 3;
		inline constexpr static std::uint8_t kSpritesheetR = 4;
		inline constexpr static std::uint8_t kSpritesheetTileSize = 48;
		inline constexpr static std::uint8_t kSpritesheetW = kSpritesheetC * kSpritesheetTileSize;
		inline constexpr static std::uint8_t kSpritesheetH = kSpritesheetR * kSpritesheetTileSize;
	public:
		void update(entt::registry& registry, shared::SharedTextures& sharedTextures, float dt);
	};
}


#endif