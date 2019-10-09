#ifndef __APP_GAME_COMPONENTS_ANIMATION_H__
#define __APP_GAME_COMPONENTS_ANIMATION_H__

#include <SDL.h>
#include <vector>
#include "../types.h"

namespace app::game::components {
	struct ComAnimation {
		using index_container_t = std::vector<std::uint8_t>;

		index_container_t indices;
		SpritesheetHandler spritesheetHandler{};
		float timer{};
		float speed{};

	};

}


#endif