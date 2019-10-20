#define SDL_MAIN_HANDLED

#include <random>
#include <SDL.h>
#include <yuu/time.h>
#include <yuu/utils.h>
#include <constants.h>
#include <assert.h>
#include <iostream>
#include <optional>
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
#pragma comment(lib, "lib/sdl_ttf/lib/x64/SDL2_ttf.lib")
#elif ENVIRONMENT32
#pragma comment(lib, "lib/sdl2/lib/x86/SDL2main.lib")
#pragma comment(lib, "lib/sdl2/lib/x86/SDL2.lib")
#pragma comment(lib, "lib/sdl2_image/lib/x86/SDL2_image.lib")
#pragma comment(lib, "lib/sdl_ttf/lib/x86/SDL2_ttf.lib")
#endif

using namespace app;
using namespace yuu;

SDL_WindowUniquePtr initSDL() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}

	if (TTF_Init() != 0) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}
	

	auto window = SDL_CreateWindow(
		"Karu's Dream",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		gDisplayWidth,
		gDisplayHeight,
		SDL_WINDOW_SHOWN);

	if (!window) {
		SDL_Log(SDL_GetError());
		return SDL_WindowUniquePtr(nullptr);
	}

	auto renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr) {
		SDL_Log(SDL_GetError());
		return nullptr;
	}

	return SDL_WindowUniquePtr(window);
}

int main(int argc, char* argv[]) {

	auto window = initSDL();
	if (!window)
		return 1;

	Time time;
	

	// Create the app
	Root{ (*window), time }.run();
	
	return 0;
}