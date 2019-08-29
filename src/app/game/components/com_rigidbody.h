#ifndef __APP_GAME_PHYSICS_H__
#define __APP_GAME_PHYSICS_H__

#include <ryoji/vector.h>

namespace app::game::components {
	struct ComRigidBody {
		ryoji::math::Vec2f velocity;
		ryoji::math::Vec2f acceleration;
	};

}


#endif