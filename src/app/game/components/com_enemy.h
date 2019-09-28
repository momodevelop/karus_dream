#ifndef __APP_GAME_COMPONENTS_ENEMY_H__
#define __APP_GAME_COMPONENTS_ENEMY_H__

#include <bitset>

namespace app::game::components {
	struct ComEnemy {
		enum States {
			STATE_MOVING_LEFT,
			STATE_MOVING_RIGHT,
			STATE_DIE
		} state{ STATE_MOVING_RIGHT };

		uint8_t hp{ 3 };
		uint8_t score{ 1 };

		float hitCooldownTimer{ 0.f };
		float hitCooldownDuration{ 0.f };
	};
}


#endif