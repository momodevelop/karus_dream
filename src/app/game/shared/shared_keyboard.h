#ifndef __APP_GAME_SHARED_KEYBOARD_H__
#define __APP_GAME_SHARED_KEYBOARD_H__

#include <bitset>
#include <unordered_map>
#include <SDL.h>

namespace app::game::shared {
	class SharedKeyboard {
	public:
		enum Handler {
			UP,
			DOWN,
			LEFT,
			RIGHT,
			Z,
			MAX
		};

		bool init();
		void handleEvent(SDL_Event& e);
		bool isKeyPressed(Handler index);

	private:
		std::unordered_map<SDL_Keycode, Handler> mappings;
		std::bitset<MAX> keyboard;

	};
}


#endif