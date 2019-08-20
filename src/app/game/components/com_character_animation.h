#ifndef __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__
#define __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__

#include <constants.h>
#include "../shared/shared_character_animations.h"


namespace app::game::components {
	struct ComCharacterAnimation {
		shared::SharedCharacterAnimations::Direction currentAnimeDir;
		shared::SharedCharacterAnimations::Direction nextAnimeDir;
		
		ComCharacterAnimation() noexcept :
			currentAnimeDir(shared::SharedCharacterAnimations::STOP_DOWN),
			nextAnimeDir(shared::SharedCharacterAnimations::STOP_DOWN)
		{}

	};

}


#endif