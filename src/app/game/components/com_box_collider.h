#ifndef __APP_GAME_COMPONENTS_BOX_COLLIDER_H__
#define __APP_GAME_COMPONENTS_BOX_COLLIDER_H__

#include <ryoji/rect.h>

namespace app::game::components {
	using namespace ryoji::math;
	
	struct ComBoxCollider {
		Rectf collider = { 0.f, 0.f, 0.f, 0.f };
	//	bool isTrigger = false;
	};

}


#endif