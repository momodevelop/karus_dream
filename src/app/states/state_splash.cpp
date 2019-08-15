#include <ryoji/vector.h>
#include <ryoji/easing.h>
#include <ryoji/common.h>
#include <yuu/utils.h>
#include <constants.h>
#include <SDL.h>
#include <SDL_image.h>

#include "state_splash.h"


using namespace ryoji;
using namespace math;
using namespace yuu;

namespace app {

	StateSplash::StateSplash(
		SDL_Renderer& renderer, 
		std::function<void()> completedCallback
	) noexcept :
		completedCallback(completedCallback),
		timer(0.f),
		stateUpdate(&StateSplash::stateIntroUpdate),
		splashRects{},
		textures{}
	{

		textures = {
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, "img/karu.png")),
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, "img/sui.png")),
		};

		// Initialize everything here
		splashRects = {
			SplashRectData {
				Vec2f { -kRectSize, gDisplayHalfHeight - kRectHalfSize },
				Vec2f { gDisplayHalfWidth - kRectSize, gDisplayHalfHeight - kRectHalfSize },
				Vec2f { kRectSize, kRectSize },
				TEXTURE_KARU,
			},
			
			SplashRectData {
				Vec2f { gDisplayWidth, gDisplayHalfHeight - kRectHalfSize },
				Vec2f { gDisplayHalfWidth, gDisplayHalfHeight - kRectHalfSize },
				Vec2f { kRectSize, kRectSize },
				TEXTURE_SUI,
			},
		};
		
	}

	StateSplash::~StateSplash() noexcept
	{		
		SDL_Log("splash::StateSplash::~StateSplash()");
	}

	void StateSplash::onEnter() noexcept
	{
		SDL_Log("splash::StateSplash::onEnter()");
	}

	void StateSplash::onUpdate(float dt) noexcept
	{
		(this->*stateUpdate)(dt);
	}

	void StateSplash::onExit() noexcept
	{
		SDL_Log("splash::StateSplash::onExit()");
	}

	void StateSplash::onRender(SDL_Renderer& renderer) noexcept
	{
		std::for_each(splashRects.cbegin(), splashRects.cend(), [&renderer, this](const SplashRectData& splashRect) {
			SDL_Rect destRect = SDL_Rect { 
				(int)splashRect.current.x, 
				(int)splashRect.current.y, 
				(int)splashRect.size.x, 
				(int)splashRect.size.y 
			};
			SDL_SetTextureAlphaMod(textures[splashRect.textureHandler].get(), splashRect.alpha);
			SDL_RenderCopy(&renderer, textures[splashRect.textureHandler].get(), NULL, &destRect);
		});
		
	}

	void StateSplash::onHandleEvent(SDL_Event& e) noexcept
	{
		switch (e.type) {
		case SDL_EventType::SDL_MOUSEBUTTONDOWN:
		case SDL_EventType::SDL_KEYDOWN:
			completedCallback();
			break;
		}
	}

	void StateSplash::onClean() noexcept
	{
	}

	void StateSplash::stateIntroUpdate(float dt) noexcept
	{
		float ease = easing::easeOutBounce(clamp(0.f, 1.0f, timer / kDuration));
		std::for_each(splashRects.begin(), splashRects.end(), [ease](SplashRectData& splashRect) {
			Vec2f delta = splashRect.end - splashRect.start;
			splashRect.current = splashRect.start + delta * ease;
		});
		
		
		if (timer > kDuration) {
			timer = 0.f;
			stateUpdate = &StateSplash::stateOutroUpdate;
		}

		timer += dt;
	}
	void StateSplash::stateOutroUpdate(float dt) noexcept
	{
		float a = clamp(0.f, kDuration, timer / kDuration);
		if (timer > kDuration) {
			completedCallback();
			return;
		}
		
		std::for_each(splashRects.begin(), splashRects.end(), [a](SplashRectData& splashRect) {
			splashRect.alpha = 255 + (Uint8)(a * -255);
		});
		
		timer += dt;
	}

}