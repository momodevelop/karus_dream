#ifndef __APP_SPLASH_SPLASH_STATE_H__
#define __APP_SPLASH_SPLASH_STATE_H__

#include <array>
#include <ryoji/vector.h>
#include <yuu/utils.h>
#include "SDL.h"
#include "state_base.h"

namespace app {
	
	class Root;
	class StateSplash : public StateBase {
		using Vec2f = ryoji::math::Vec2f;

		enum { RECT_NUM = 2 };

		enum TextureEnum : Uint8 {
			TEXTURE_KARU,
			TEXTURE_SUI,
			TEXTURE_MAX
		};

		static constexpr float kDuration = 1.f;
		static constexpr float kRectSize = 240.f;
		static constexpr float kRectHalfSize = kRectSize / 2.f;

		
		struct SplashRectData {
			Vec2f current;
			Vec2f start;
			Vec2f end;
			Vec2f size;
			TextureEnum textureHandler;
			Uint8 alpha;

			SplashRectData(Vec2f start = {}, Vec2f end = {}, Vec2f size = {}, TextureEnum textureHandler = {})
				: start(start), end(end), size(size), textureHandler(textureHandler), 
				alpha(255), current(start)
			{
			}
		};

	private: // variables
		std::array<SplashRectData, RECT_NUM> splashRects;
		std::array<yuu::SDL_TextureUniquePtr, TEXTURE_MAX> textures;
		std::function<void()> completedCallback;
		void (StateSplash::*stateUpdate)(float dt);
		float timer;

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