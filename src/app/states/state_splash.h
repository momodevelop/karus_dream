#ifndef __APP_SPLASH_SPLASH_STATE_H__
#define __APP_SPLASH_SPLASH_STATE_H__

#include <functional>
#include "SDL.h"
#include "state_base.h"

#include "../../image/texture_shelf.h"


namespace app::splash {
	class StateBase;
	class StateIntro;
	class StateOutro;
}

namespace app {
	
	class Root;
	class StateSplash : public StateBase {
		enum { RECT_NUM = 2 };
		enum TextureEnum {
			TEXTURE_KARU,
			TEXTURE_SUI,
			TEXTURE_MAX
		};

	private: // variables
		SDL_Rect splashRects[RECT_NUM];
		float timer;
		Uint8 alpha;

		image::TextureShelf<TEXTURE_MAX> textureShelf;		
		std::function<void()> completedCallback;

		void (StateSplash::*stateUpdate)(float dt);
		void (StateSplash::*stateHandleEvent)(SDL_Event& e);
	private:
		void stateIntroUpdate(float dt) noexcept;
		void stateOutroUpdate(float dt) noexcept;


	public:
		StateSplash(
			SDL_Renderer& renderer, 
			std::function<void()> completedCallback
		) noexcept;
		~StateSplash() noexcept;

		virtual void onEnter() noexcept override;
		virtual void onUpdate(float dt) noexcept override;
		virtual void onExit() noexcept override;
		virtual void onRender(SDL_Renderer& renderer) noexcept override;
		virtual void onHandleEvent(SDL_Event& e) noexcept override;
		virtual void onClean() noexcept override;
	};


}
#endif