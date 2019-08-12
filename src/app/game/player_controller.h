#ifndef __APP_GAME_CHARACTER_CONTROLLER_H__
#define __APP_GAME_CHARACTER_CONTROLLER_H__

#include "SDL.h"

namespace app::game {

	struct iPlayerControllable;
	class PlayerController {
		iPlayerControllable * playerControllable;
	public:
		PlayerController(iPlayerControllable * = nullptr) noexcept;

		inline void setCharacter(iPlayerControllable * pc) noexcept { playerControllable = pc; }
		inline bool isControlling() const noexcept { return playerControllable != nullptr; }
		void handleInput(SDL_Event& e) noexcept;
	};

}


#endif