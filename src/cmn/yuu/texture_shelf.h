#ifndef __IMAGE_TEXTURE_SHELF_H__
#define __IMAGE_TEXTURE_SHELF_H__

#include <cassert>
#include "SDL_image.h"


namespace yuu {

	// Simple class that wraps an array of SDL_Surfaces
	// 
	template<size_t Size>
	class TextureShelf {
		SDL_Texture * textures[Size];

		TextureShelf(const TextureShelf&) = delete;
		TextureShelf& operator=(const TextureShelf&) = delete;

	public:
		TextureShelf() noexcept {
			for (size_t i = 0; i < Size; ++i) {
				textures[i] = nullptr;
			}
		}
		virtual ~TextureShelf() noexcept {
			for (size_t i = 0; i < Size; ++i) {
				unload(i);
			}
		}

		bool load(SDL_Renderer * renderer, size_t index, SDL_Surface * surface, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND) noexcept
		{
			assert(renderer != nullptr);
			assert(index >= 0 && index < Size);
			textures[index] = SDL_CreateTextureFromSurface(renderer, surface);
			if (textures[index] == nullptr) {
				SDL_Log(IMG_GetError());
				return false;
			}
			SDL_SetTextureBlendMode(textures[index], blendMode);
			return true;
		}
		bool load(SDL_Renderer * renderer, size_t index, const char * path, SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND) noexcept
		{
			assert(renderer != nullptr);
			assert(path != nullptr);
			assert(index >= 0 && index < Size);

			SDL_Surface * surface = IMG_Load(path);
			if (surface == nullptr) {
				SDL_Log(IMG_GetError());
				return false;
			}
			
			bool success = loadFromSurface(renderer, index, surface);
			SDL_FreeSurface(surface);

			return success;

		}
		void unload(size_t index) noexcept
		{
			assert(index >= 0 && index < Size);
			if (textures[index] != nullptr) {
				SDL_DestroyTexture(textures[index]);
				textures[index] = nullptr;
			}
		}

		void unloadAll() noexcept 
		{
			for (size_t index = 0; index < Size; ++index) {
				unload(index);
			}
		}

		SDL_Texture* operator[](size_t index) noexcept {
			assert(index >= 0 && index < Size);
			return textures[index];
		}
		const SDL_Texture* operator[](size_t index) const noexcept {
			assert(index >= 0 && index < Size);
			return textures[index];
		}


	};
}


#endif