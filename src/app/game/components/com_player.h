#ifndef __APP_GAME_COMPONENTS_PLAYER_H__
#define __APP_GAME_COMPONENTS_PLAYER_H__

#include <entt.h>
#include <array>

namespace app::game::components {
	struct ComPlayer {
		float jumpCooldown{ 0.5f };
		float jumpTimer{};
		std::array<entt::entity,2> jumpTriggers;
		entt::entity weaponTrigger;
	};
}


#endif