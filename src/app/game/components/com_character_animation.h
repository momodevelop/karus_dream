#ifndef __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__
#define __APP_GAME_COMPONENTS_CHARACTER_ANIMATION_H__

#include <constants.h>
#include "../shared/shared_animation_indices.h"


namespace app::game::components {
	struct ComCharacterAnimation {
		shared::SharedAnimationIndices::Indices currentAnimeDir;
		shared::SharedAnimationIndices::Indices nextAnimeDir;
		
		ComCharacterAnimation() noexcept :
			currentAnimeDir(shared::SharedAnimationIndices::CHARACTER_STOP_DOWN),
			nextAnimeDir(shared::SharedAnimationIndices::CHARACTER_STOP_DOWN)
		{}

	};

}


#endif