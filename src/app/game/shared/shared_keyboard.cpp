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
		if (e.type == SDL_KEYDOWN) {
			const auto& itr = mappings.find(e.key.keysym.sym);
			if(itr != mappings.cend())
				keyboard[itr->second] = true;
		}

		else if (e.type == SDL_KEYUP) {
			const auto& itr = mappings.find(e.key.keysym.sym);
			if (itr != mappings.cend())
				keyboard[itr->second] = false;
		}
	}
	
	bool SharedKeyboard::isKeyPressed(Handler index)
	{
		return keyboard[index];
	}
}