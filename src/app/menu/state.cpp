#include <ryoji/vector.h>
#include <ryoji/easing.h>
#include <ryoji/common.h>
#include <yuu/utils.h>
#include <constants.h>
#include <SDL.h>
#include <SDL_image.h>

#include "state.h"


using namespace ryoji;
using namespace math;
using namespace yuu;

namespace app::menu {

	State::State(
		SDL_Renderer& renderer,
		std::function<void()> completedCallback
	) noexcept :
		completedCallback(completedCallback),
		textures {
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, "img/karu.png")),
		}
	{
	}

	State::~State() noexcept
	{
	}

	void State::onEnter() noexcept
	{
	}

	void State::onUpdate(float dt) noexcept
	{
	}

	void State::onExit() noexcept
	{
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{

	}

	void State::onHandleEvent(SDL_Event& e) noexcept
	{
		/*switch (e.type) {
		case SDL_EventType::SDL_MOUSEBUTTONDOWN:
		case SDL_EventType::SDL_KEYDOWN:
			completedCallback();
			break;
		}*/
	}

	void State::onClean() noexcept
	{
	}


}