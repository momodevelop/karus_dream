#ifndef __YUU_TEXTURE_MANAGER_H__
#define __YUU_TEXTURE_MANAGER_H__

#include <SDL.h>
#include <yuu/utils.h>
#include <array>

namespace yuu {
	template<typename Handler>
	class TextureManager {
	public:
		struct TextureData {
			yuu::SDL_TextureUniquePtr texture;
			Handler handler;
			int width, height;
		};

	private:
		std::unordered_map<Handler, TextureData> textures;

	public:
		inline const TextureData& operator[](Handler index) const {
			return textures.at(index);
		}

		bool addTexture(SDL_Renderer& renderer, Handler handler, const char * path)
		{
			auto ptr = SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, path));
			int w, h;
			SDL_QueryTexture(ptr.get(), NULL, NULL, &w, &h);
			textures[handler] = TextureData{ std::move(ptr), handler, w, h };

			if (!textures[handler].texture)
				return false;
			return true;
		}
		bool addTexture(SDL_Renderer& renderer, Handler handler, SDL_Surface* surface) {
			auto ptr = SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromSurfaceX(&renderer, surface));
			int w, h;
			SDL_QueryTexture(ptr.get(), NULL, NULL, &w, &h);
			textures[handler] = TextureData{ std::move(ptr), handler, w, h };

			if (!textures[handler].texture)
				return false;
			return true;
		}

		bool addText(SDL_Renderer& renderer, TTF_Font* font, Handler handler, SDL_Color color, const char * text) {
			if (font == nullptr)
				return false;
			auto* surface = TTF_RenderText_Solid(font, text, color);
			if (!addTexture(renderer, handler, surface)) {
				return false;
			}
			return true;
		}




	};
}

#endif
