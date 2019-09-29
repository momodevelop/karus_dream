#ifndef __APP_GAME_COMPONENTS_PLAYER_H__
#define __APP_GAME_COMPONENTS_PLAYER_H__

#include <entt.h>
#include <array>

namespace app::game::components {
	struct ComPlayer {
		enum States {
			STATE_IDLE,
			STATE_MOVING_LEFT,
			STATE_MOVING_RIGHT,
			STATE_DIE
		} state{ STATE_IDLE };

		float jumpCooldown{ 0.5f };
		float jumpTimer{};
		std::array<entt::entity,2> jumpTriggers;
		entt::entity weaponTrigger;

	};
}


#endif