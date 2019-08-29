#ifndef __APP_GAME_COMPONENTS_GRAVITY_H__
#define __APP_GAME_COMPONENTS_GRAVITY_H__

#include <ryoji/vector.h>

namespace app::game::components {
	struct ComConstantForce {
		ryoji::math::Vec2f force;
	};
}


#endif