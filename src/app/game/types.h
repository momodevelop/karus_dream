#ifndef __APP_GAME_TYPES_H__
#define __APP_GAME_TYPES_H__

#include <yuu/utils.h>

namespace app::game {


	enum KeyboardHandler {
		KB_UP,
		KB_DOWN,
		KB_LEFT,
		KB_RIGHT,
		KB_Z,
		KB_MAX 
	};
	using keyboard_t = std::bitset<KB_MAX>;
}

#endif