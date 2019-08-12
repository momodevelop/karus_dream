#include "player_controller.h"
#include "i_player_controllable.h"

namespace app::game {
	PlayerController::PlayerController(iPlayerControllable * pc) noexcept
		: playerControllable(pc)
	{
	}

	void PlayerController::handleInput(SDL_Event & e) noexcept
	{
		if (!isControlling()) {
			return;
		}

		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				playerControllable->startMove(iPlayerControllable::MOVE_LEFT);
				break;
			case SDLK_RIGHT:
				playerControllable->startMove(iPlayerControllable::MOVE_RIGHT);
				break;
			case SDLK_UP:
				playerControllable->startMove(iPlayerControllable::MOVE_UP);
				break;
			case SDLK_DOWN:
				playerControllable->startMove(iPlayerControllable::MOVE_DOWN);
				break;
			default:
				break;
			}
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				playerControllable->stopMove(iPlayerControllable::MOVE_LEFT);
				break;
			case SDLK_RIGHT:
				playerControllable->stopMove(iPlayerControllable::MOVE_RIGHT);
				break;
			case SDLK_UP:
				playerControllable->stopMove(iPlayerControllable::MOVE_UP);
				break;
			case SDLK_DOWN:
				playerControllable->stopMove(iPlayerControllable::MOVE_DOWN);
				break;
			default:
				break;
			}
		}
	}
}
