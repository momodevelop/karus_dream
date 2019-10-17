#ifndef __APP_GAME_SHARED_GAME_STATE_H__
#define __APP_GAME_SHARED_GAME_STATE_H__

#include <vector>

namespace app::game::shared {

	class SharedGameState {
	public:
		enum States {
			GAME_START,
			GAME_UPDATE,
			GAME_OVER,
			GAME_OVER_DONE,
		} state{ GAME_START };
	};

}

#endif
 