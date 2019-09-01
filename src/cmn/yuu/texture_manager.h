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

		struct SpritesheetData {
			std::vector<SDL_Rect> frames;
			int rows, cols;
		};

	public:
		inline TextureData& operator[](Handler index) {
			return textures.at(index);
		}

		inline const TextureData& operator[](Handler index) const {
			return textures.at(index);
		}

		inline const SpritesheetData& getSpritesheetData(Handler index) const {
			return spritesheetDatas.at(index);
		}

		inline const SDL_Rect& getFrame(Handler index, size_t frameIndex) const {
			return spritesheetDatas.at(index).frames.at(frameIndex);
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


		bool addSpritesheet(SDL_Renderer& renderer, Handler handler, const char * path, int rows, int cols)
		{
			if (!addTexture(renderer, handler, path)) {
				return false;
			}
			auto& textureData = textures[handler];
			return addSpritesheetData(handler, textureData.width, textureData.height, rows, cols);

		}

		bool addSpritesheet(SDL_Renderer& renderer, Handler handler, SDL_Surface * surface, int rows, int cols) {
			if (!addTexture(renderer, handler, surface)) {
				return false;
			}
			auto& textureData = textures[handler];
			return addSpritesheetData(handler, textureData.width, textureData.height, rows, cols);
			
		}

	private:
		bool addSpritesheetData(Handler handler, int width, int height, int rows, int cols) {
			auto& data = spritesheetDatas[handler];
			data.rows = rows;
			data.cols = cols;


			int tileWidth = width / cols;
			int tileHeight = height / rows;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					auto index = j + cols * i;
					data.frames.emplace_back(SDL_Rect{
						j * tileWidth,
						i * tileHeight,
						tileWidth,
						tileHeight
					});
				}
			}

			return true;
		}

		std::unordered_map<Handler, TextureData> textures;
		std::unordered_map<Handler, SpritesheetData> spritesheetDatas;

	};
}

#endif
