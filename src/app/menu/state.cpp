#include <ryoji/vector.h>
#include <ryoji/easing.h>
#include <ryoji/common.h>
#include <yuu/utils.h>
#include <constants.h>
#include <SDL.h>
#include <SDL_image.h>

#include <cassert>

#include "state.h"
#include "types.h"


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
		if (!sharedTextures.addTexture(renderer, GRID_SPRITESHEET, "img/plains.png", 80, 48, 3, 5)) {
			assert(false);
		}

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
		renderBackground(renderer);

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

	void State::renderBackground(SDL_Renderer & renderer)
	{
		auto& textures = sharedTextures;
		auto& textureData = textures[TextureHandler::GRID_SPRITESHEET];
		{
			float offset = gDisplayWidth / 20;

			int ii = 0;
			for (float i = 0.f; i < gDisplayWidth; i += offset, ++ii) {
				int jj = 0;
				for (float j = 0.f; j < gDisplayHalfHeight; j += offset, ++jj) {

					SDL_Rect destRect = {
						int(i),
						int(j),
						int(offset),
						int(offset)
					};


					SDL_SetTextureAlphaMod(textureData.texture.get(), 255);
					if (jj == 4)
						SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, 8), &destRect);
					else
						SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, 2), &destRect);
				}
			}
			{
				float offset = gDisplayWidth / 20;
				for (float i = 0.f; i < gDisplayWidth; i += offset) {

					int k = 0;
					for (float j = gDisplayHalfHeight; j < gDisplayHeight; j += offset, ++k) {
						// top
						SDL_Rect destRect = {
							int(i),
							int(j),
							int(offset),
							int(offset)
						};
						int index = 11;
						if (k == 0)	index = 0;
						else if (k == 1) index = 6;

						SDL_SetTextureAlphaMod(textureData.texture.get(), 255);
						SDL_RenderCopy(&renderer, textureData.texture.get(), &textures.getFrame(textureData.handler, index), &destRect);
					}
				}
			}
		}
	}
}