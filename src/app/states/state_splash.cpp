#include <ryoji/vector.h>
#include <ryoji/easing.h>
#include <ryoji/common.h>
#include <constants.h>
#include <SDL.h>
#include <SDL_image.h>

#include "state_splash.h"


using namespace ryoji;
using namespace math;


namespace app {

	static const float kDuration = 1.f;
	static constexpr float kRectSize = 240.f;

	static const Vec2f kSplashImageOrigin[] = {
		{-kRectSize, kDisplayHeight / 2 - kRectSize / 2},		//left
		{(float)kDisplayWidth, (float)kDisplayHeight / 2 - kRectSize / 2},	//right
	};

	static const Vec2f kSplashImageDest[] = {
		{(float)kDisplayWidth / 2 - kRectSize, kDisplayHeight / 2 - kRectSize / 2 }, //left
		{(float)kDisplayWidth / 2, (float)kDisplayHeight / 2 - kRectSize / 2 },	//right
	};

	StateSplash::StateSplash(
		SDL_Renderer& renderer, 
		std::function<void()> completedCallback) noexcept :
			completedCallback(completedCallback),
			timer(0.f),
			alpha(255),
			stateUpdate(&StateSplash::stateIntroUpdate)
	{
		textureShelf.loadFromPath(&renderer, TEXTURE_KARU, "img/karu.png");
		textureShelf.loadFromPath(&renderer, TEXTURE_SUI, "img/sui.png");

		for (int i = 0; i < StateSplash::RECT_NUM; ++i)
			splashRects[i] = { (int)kSplashImageOrigin[i].x, (int)kSplashImageOrigin[i].y, (int)kRectSize, (int)kRectSize };

	}

	StateSplash::~StateSplash() noexcept
	{
		
		SDL_Log("splash::StateSplash::~StateSplash()");
		textureShelf.unloadAll();
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
		SDL_SetTextureAlphaMod(textureShelf[StateSplash::TEXTURE_KARU], alpha);
		SDL_RenderCopy(&renderer, textureShelf[StateSplash::TEXTURE_KARU], NULL, &splashRects[0]);

		SDL_SetTextureAlphaMod(textureShelf[StateSplash::TEXTURE_SUI], alpha);
		SDL_RenderCopy(&renderer, textureShelf[StateSplash::TEXTURE_SUI], NULL, &splashRects[1]);
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
		for (int i = 0; i < StateSplash::RECT_NUM; ++i) {
			Vec2f delta = kSplashImageDest[i] - kSplashImageOrigin[i];
			Vec2f currentPosition = kSplashImageOrigin[i] + delta * ease;
			splashRects[i].x = (int)currentPosition.x;
			splashRects[i].y = (int)currentPosition.y;
		}
			
		
		
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
		alpha = 255 + (Uint8)(a * -255);
		timer += dt;
	}

}