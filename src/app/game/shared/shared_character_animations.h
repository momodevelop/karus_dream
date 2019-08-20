#ifndef __APP_GAME_SHARED_CHARACTER_ANIMATIONS_H__
#define __APP_GAME_SHARED_CHARACTER_ANIMATIONS_H__

#include <vector>

namespace app::game::shared {

	// Stores indices to character animations
	class SharedCharacterAnimations {
	public:
		using indices_t = std::vector<std::uint8_t>;
		using indices_set_t = std::vector<indices_t>;

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

		bool init();
		
		inline const indices_t& operator[](Direction index) {
			return indicesSet[index];
		}

	private:
		indices_set_t indicesSet;
	};

}

#endif
