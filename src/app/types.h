#ifndef __APP_TYPES_H__
#define __APP_TYPES_H__

namespace app {
	enum StateEnum : uint8_t {
		STATE_NONE,
		STATE_SPLASH,
		STATE_MENU,
		STATE_GAME,
		STATE_EXIT,
	};
}

#endif