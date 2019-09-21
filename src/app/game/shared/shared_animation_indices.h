#ifndef __APP_GAME_SHARED_ANIMATION_INDICES_H__
#define __APP_GAME_SHARED_ANIMATION_INDICES_H__

#include <vector>

namespace app::game::shared {

	class SharedAnimationIndices {
	public:
		using indices_t = std::vector<std::uint8_t>;
		using indices_set_t = std::vector<indices_t>;

		enum Indices {
			CHARACTER_NORM_DOWN,
			CHARACTER_NORM_LEFT,
			CHARACTER_NORM_RIGHT,
			CHARACTER_NORM_UP,
			
			CHARACTER_STOP_DOWN,
			CHARACTER_STOP_LEFT,
			CHARACTER_STOP_RIGHT,
			CHARACTER_STOP_UP,

			COIN,

			ENEMY_BAT,
			ENEMY_FROG,
			ENEMY_GHOST,
			ENEMY_SKELETON,

			MAX
		};

		bool init();
		
		inline const indices_t& operator[](Indices index) {
			return indicesSet[index];
		}

	private:
		indices_set_t indicesSet;
	};

}

#endif
