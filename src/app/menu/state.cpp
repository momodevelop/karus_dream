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
		std::function<void()> startCallback,
		std::function<void()> quitCallback
	) noexcept :
		startCallback(startCallback),
		quitCallback(quitCallback),
		currentSelection(0)
	{

		auto font = TTF_OpenFont("img/arcade.ttf", 24);
		if (!font) {
			SDL_Log("Failed: %s\n", SDL_GetError());
			assert(false);
		}

		auto* titleSurface = TTF_RenderText_Solid(font, "Karu's Dream", { 255, 255, 255 });
		auto* arrowSurface = TTF_RenderText_Solid(font, ">", { 255, 255, 255 });
		auto* startSurface = TTF_RenderText_Solid(font, "Start ", { 255, 255, 255 });
		auto* quitSurface = TTF_RenderText_Solid(font, "Quit", { 255, 255, 255 });
		auto* madeBySurface = TTF_RenderText_Solid(font, "A simple game by Gerald Wong (Momo)", { 255, 255, 255 });

		if (!sharedTextures.addSpritesheet(renderer, GRID_SPRITESHEET, "img/plains.png", 3, 5) ||
			!sharedTextures.addTexture(renderer, TITLE, titleSurface) ||
			!sharedTextures.addTexture(renderer, ARROW, arrowSurface) ||
			!sharedTextures.addTexture(renderer, START, startSurface) ||
			!sharedTextures.addTexture(renderer, QUIT, quitSurface) ||
			!sharedTextures.addTexture(renderer, MADE_BY, madeBySurface)			
			)
		{
			SDL_Log("Failed: %s\n", SDL_GetError());
			assert(false);
		}

		TTF_CloseFont(font);


		
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
		renderTexts(renderer);


	}

	void State::onHandleEvent(SDL_Event& e) noexcept
	{
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {

			switch (e.key.keysym.sym) {
			case SDLK_UP:
				--currentSelection;
				break;
			case SDLK_DOWN:
				++currentSelection;
				break;
			case SDLK_z:
				switch (currentSelection) {
				case 0: // Start
					startCallback();
					break;
				case 1: // Quit
					quitCallback();
					break;
				};
				break;
			}
		}
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
	void State::renderTexts(SDL_Renderer & renderer)
	{
		// render title
		renderTextAt(renderer, TITLE, gDisplayHalfWidth - gDisplayHalfWidth / 2, 80, 2.f);
	
		// render menu
		Vec2i startPosition = { gDisplayHalfWidth - 60, 230 };
		Vec2i quitPosition = { gDisplayHalfWidth - 50, 280 };

		renderTextAt(renderer, START, startPosition.x, startPosition.y, 1.2f);
		renderTextAt(renderer, QUIT, quitPosition.x, quitPosition.y, 1.2f);
		
		// render arrow
		switch (currentSelection % 2) {
		case 1: // QUIT
			renderTextAt(renderer, ARROW, quitPosition.x - 30, quitPosition.y, 1.2f);
			break;
		default: // START 
			renderTextAt(renderer, ARROW, startPosition.x - 30, startPosition.y, 1.2f);
		}


		// render made by
		renderTextAt(renderer, MADE_BY, 10, gDisplayHeight - 22, 0.8f);
	}
	void State::renderTextAt(SDL_Renderer & renderer, TextureHandler handler, int x, int y, float scale)
	{
		int w, h;
		SDL_QueryTexture(sharedTextures[handler].texture.get(), 0, 0, &w, &h);
		SDL_Rect destRec = { x, y, int(w * scale), int(h * scale) };
		SDL_RenderCopy(&renderer, sharedTextures[handler].texture.get(), nullptr, &destRec);
	}
}