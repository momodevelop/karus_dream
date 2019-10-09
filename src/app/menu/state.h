#ifndef __APP_SPLASH_MENU_STATE_H__
#define __APP_SPLASH_MENU_STATE_H__


#include <SDL.h>
#include <yuu/utils.h>
#include <yuu/texture_manager.h>
#include <yuu/spritesheet_manager.h>
#include <SDL_ttf.h>


#include "types.h"
#include "../state_base.h"


namespace app::menu {

	class State : public StateBase {


	private: // variables

		std::function<void()> startCallback;
		std::function<void()> quitCallback;
		
		yuu::TextureManager<TextureHandler> sharedTextures;
		yuu::SpritesheetManager<SpritesheetHandler> sharedSpritesheets;
		SDL_Texture* textTexture;

		int currentSelection;

		void renderBackground(SDL_Renderer& renderer);
		void renderTexts(SDL_Renderer& renderer);
		void renderTextAt(SDL_Renderer & renderer, TextureHandler handler, int x, int y, float scale);
	public:
		State(
			SDL_Renderer& renderer,
			std::function<void()> startCallback,
			std::function<void()> quitCallback
		) noexcept;
		~State() noexcept;

		virtual void onEnter() noexcept override;
		virtual void onUpdate(float dt) noexcept override;
		virtual void onExit() noexcept override;
		virtual void onRender(SDL_Renderer& renderer) noexcept override;
		virtual void onHandleEvent(SDL_Event& e) noexcept override;
		virtual void onClean() noexcept override;
	};


}
#endif