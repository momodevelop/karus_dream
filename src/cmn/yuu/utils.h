// A bunch of functions and typedefs to provide my own abstractions to SDL functions
#ifndef __YUU_UTILS_H__
#define __YUU_UTILS_H__

#include <functional>
#include "SDL.h"
#include "SDL_image.h"

namespace yuu {
	template<auto Func>
	struct Functorize {
		template<typename... Args>
		auto operator()(Args&&...args) {
			return std::invoke(Func, std::forward<Args>(args)...);
		}
	};

	SDL_Texture* SDL_CreateTextureFromSurfaceX(
		SDL_Renderer * renderer,
		SDL_Surface * surface,
		SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

	SDL_Texture* SDL_CreateTextureFromPathX(
		SDL_Renderer * renderer,
		const char * path,
		SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

	SDL_Surface* SDL_CreateSurfaceFromPathX(
		SDL_Renderer* renderer,
		const char* path
	);

	using SDL_TextureUniquePtr = std::unique_ptr<SDL_Texture, Functorize<SDL_DestroyTexture>>;
	using SDL_WindowUniquePtr = std::unique_ptr<SDL_Window, Functorize<SDL_DestroyWindow>>;
	using SDL_SurfaceUniquePtr = std::unique_ptr<SDL_Surface, Functorize<SDL_FreeSurface>>;

}

#endif