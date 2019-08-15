#ifndef __APP_SPLASH_SPLASH_STATE_H__
#define __APP_SPLASH_SPLASH_STATE_H__

#include <array>
#include <ryoji/vector.h>
#include <yuu/utils.h>
#include <SDL.h>

#include "rect_data.h"
#include "types.h"

#include "../state_base.h"


namespace app::splash {
	
	class Root;
	class State : public StateBase {
		using Vec2f = ryoji::math::Vec2f;

	public:
		enum { RECT_NUM = 2 };

		static constexpr float kDuration = 1.f;
		static constexpr float kRectSize = 240.f;
		static constexpr float kRectHalfSize = kRectSize / 2.f;

		


	private: // variables
		std::array<RectData, RECT_NUM> splashRects;
		std::array<yuu::SDL_TextureUniquePtr, TEXTURE_MAX> textures;
		std::function<void()> completedCallback;
		void (State::*stateUpdate)(float dt);
		float timer;

	private:
		void stateIntroUpdate(float dt) noexcept;
		void stateOutroUpdate(float dt) noexcept;


	public:
		State(
			SDL_Renderer& renderer, 
			std::function<void()> completedCallback
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