#ifndef __APP_GAME_COMPONENTS_BOX_COLLIDER_H__
#define __APP_GAME_COMPONENTS_BOX_COLLIDER_H__

#include <ryoji/aabb.h>

namespace app::game::components {
	struct ComBoxCollider {
		ryoji::aabb::AABB2f box{};
	};

}


#endif