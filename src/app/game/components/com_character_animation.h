#ifndef __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__
#define __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__

#include <constants.h>


namespace app::game::components {
	struct ComCharacterAnimation {
		character::animation::Direction currentAnimeDir;
		character::animation::Direction nextAnimeDir;
		bool stop;

		ComCharacterAnimation() noexcept :
			currentAnimeDir(character::animation::FRONT),
			nextAnimeDir(character::animation::FRONT)
		{}

	};

}


#endif