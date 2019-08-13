#define SDL_MAIN_HANDLED

#include <yuu/time.h>
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

using namespace app;

#include <iostream>
int main(int argc, char* argv[]) {

	// Create the app
	Root app;
	app.run();
	
	
	return 0;
}