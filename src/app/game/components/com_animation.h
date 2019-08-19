#ifndef __APP_GAME_COMPONENTS_ANIMATION_H__
#define __APP_GAME_COMPONENTS_ANIMATION_H__

#include <SDL.h>
#include <vector>

namespace app::game::components {
	struct ComAnimation {
		using index_container_t = std::vector<std::uint8_t>;

		index_container_t indices;
		float timer = 0.f;
		float speed = 0.f;

	};

}


#endif