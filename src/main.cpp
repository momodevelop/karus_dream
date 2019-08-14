#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <yuu/time.h>
#include <yuu/core.h>
#include <constants.h>

#include "app/root.h"

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#ifdef ENVIRONMENT64
#pragma comment(lib, "lib/sdl2/lib/x64/SDL2main.lib")
#pragma comment(lib, "lib/sdl2/lib/x64/SDL2.lib")
#pragma comment(lib, "lib/sdl2_image/lib/x64/SDL2_image.lib")
#elif ENVIRONMENT32
#pragma comment(lib, "lib/sdl2/lib/x86/SDL2main.lib")
#pragma comment(lib, "lib/sdl2/lib/x86/SDL2.lib")
#pragma comment(lib, "lib/sdl2_image/lib/x86/SDL2_image.lib")
#endif

#include <assert.h>
#include <iostream>
#include <optional>
#include <constants.h>

using namespace app;
using namespace yuu;


std::unique_ptr<SDL_Window, SDLWindowDestroyer> initSDL() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}

	auto window = SDL_CreateWindow(
		"vigil",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gDisplayWidth,
		gDisplayHeight,
		SDL_WINDOW_SHOWN);

	if (!window) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}

	auto renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}

	return std::make_unique<SDL_Window>(window);
}

int main(int argc, char* argv[]) {
	auto ret = initSDL();
	if (!ret)
		return 1;

	Time time;

	
	// Create the app
	Root root(std::move(ret), time);
	root.run();
	
	
	return 0;
}