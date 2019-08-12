#ifndef __YUU_CORE_H__
#define __YUU_CORE_H__

#include "SDL.h"

namespace yuu {
	// All SDL related cores are here.
	class Core {
		SDL_Window * window;
		SDL_Renderer * renderer;
	public:
		Core(const char * title = "",
			int w = 800,
			int h = 600, 
			int x = SDL_WINDOWPOS_CENTERED,
			int y = SDL_WINDOWPOS_CENTERED) noexcept;
		~Core() noexcept;

		SDL_Window& getWindow() noexcept;
		SDL_Renderer& getRenderer() noexcept;
	};
}


#endif