#ifndef __APP_GAME_SHARED_CHARACTER_ANIMATIONS_H__
#define __APP_GAME_SHARED_CHARACTER_ANIMATIONS_H__

#include <vector>

namespace app::game::shared {

	class SharedCharacterAnimations {
	public:

		enum Direction {
			FRONT,
			LEFT,
			RIGHT,
			BACK,

			FRONT_STOP,
			LEFT_STOP,
			RIGHT_STOP,
			BACK_STOP,

			MAX
		};

		//bool init();

	private:
		//std::vector<std::uint8_t>

	};

}

#endif
