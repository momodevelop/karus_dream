#include <assert.h>
#include "SDL.h"
#include "core.h"

using namespace yuu;

Core::Core(const char * title, int w, int h, int x, int y) noexcept :
	renderer(nullptr), window(nullptr)
{
	// SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log(SDL_GetError());
		assert(true);
	}

	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Log(SDL_GetError());
		assert(true);
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		SDL_Log(SDL_GetError());
		assert(true);
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

}

Core::~Core() noexcept {
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();

}

SDL_Window& Core::getWindow() noexcept
{
	return *window;
}

SDL_Renderer& Core::getRenderer() noexcept
{
	return *renderer;
}