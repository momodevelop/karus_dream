#ifndef __APP_GAME_COMPONENTS_TRANSFORM_H__
#define __APP_GAME_COMPONENTS_TRANSFORM_H__

#include <ryoji/vector.h>

namespace app::game::components {
	struct ComTransform {
		ryoji::math::Vec2f position{};
		ryoji::math::Vec2f scale{};
	};
}

#endif