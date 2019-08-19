#include <array>
#include "shared_keyboard.h"

namespace app::game::shared {

	struct KeyboardMapping {
		SharedKeyboard::Handler handler;
		SDL_Keycode keyCode;
	};

	static constexpr std::array<KeyboardMapping, SharedKeyboard::MAX> keyboardMappings = {
		KeyboardMapping{ SharedKeyboard::UP, SDLK_UP },
		KeyboardMapping{ SharedKeyboard::DOWN, SDLK_DOWN },
		KeyboardMapping{ SharedKeyboard::RIGHT, SDLK_RIGHT },
		KeyboardMapping{ SharedKeyboard::LEFT, SDLK_LEFT },
		KeyboardMapping{ SharedKeyboard::Z, SDLK_z },
	};

	bool SharedKeyboard::init()
	{
		for (auto& i : keyboardMappings) {
			if (!mappings.insert({ i.keyCode, i.handler }).second)
				return false;
		}
		return true;
	}

	void SharedKeyboard::handleEvent(SDL_Event & e)
	{
		keyUp.reset();
		keyDown.reset();

		if (e.type == SDL_KEYDOWN) {
			const auto& itr = mappings.find(e.key.keysym.sym);
			if (itr != mappings.cend()) {
				keyHeld[itr->second] = true;
				keyDown[itr->second] = true;
			} 
		}

		else if (e.type == SDL_KEYUP) {
			const auto& itr = mappings.find(e.key.keysym.sym);
			if (itr != mappings.cend()) {
				keyHeld[itr->second] = false;
				keyUp[itr->second] = true;
			}
		}
	}

	bool SharedKeyboard::isKeyUp(Handler index)
	{
		return keyUp[index];
	}

	bool SharedKeyboard::isKeyDown(Handler index)
	{
		return keyDown[index];
	}
	
	bool SharedKeyboard::isKeyHeld(Handler index)
	{
		return keyHeld[index];
	}
}