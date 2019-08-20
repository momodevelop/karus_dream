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
			NORM_DOWN,
			NORM_LEFT,
			NORM_RIGHT,
			NORM_UP,
			
			STOP_DOWN,
			STOP_LEFT,
			STOP_RIGHT,
			STOP_UP,

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
