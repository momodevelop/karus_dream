#ifndef __APP_GAME_SHARED_KEYBOARD_H__
#define __APP_GAME_SHARED_KEYBOARD_H__

#include <bitset>
#include <unordered_map>
#include <SDL.h>

namespace app::game::shared {
	class SharedKeyboard {
	public:
		enum Handler {
			LEFT,
			RIGHT,
			Z,
			MAX
		};

		bool init();
		void clear();
		void handleEvent(SDL_Event& e);
		bool isKeyDown(Handler index);
		bool isKeyUp(Handler index);
		bool isKeyHeld(Handler index);

	private:
		std::unordered_map<SDL_Keycode, Handler> mappings;
		std::bitset<MAX> keyHeld;
		std::bitset<MAX> keyUp;
		std::bitset<MAX> keyDown;

	};
}


#endif