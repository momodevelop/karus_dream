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
			int rows, cols;
		};

	public:
		inline TextureData& operator[](Handler index) {
			return textures.at(index);
		}

		inline const TextureData& operator[](Handler index) const {
			return textures.at(index);
		}

		inline const SDL_Rect& getFrame(Handler index, size_t frameIndex) const {
			return frames.at(index).at(frameIndex);
		}


		bool addTexture(SDL_Renderer& renderer, Handler handler, const char * path, int width, int height, int rows, int cols)
		{
			textures[handler] = TextureData{
			SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, path)),
				handler,
				width, height,
				rows, cols,
			};

			if (!textures[handler].texture)
				return false;

			// generate the SDL_Rects
			auto insertPair = frames.try_emplace(handler);
			if (!insertPair.second) {
				textures.erase(handler);
				return false;
			}


			int tileWidth = width / cols;
			int tileHeight = height / rows;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					auto index = j + cols * i;
					(*insertPair.first).second.emplace_back(SDL_Rect{
						j * tileWidth,
						i * tileHeight,
						tileWidth,
						tileHeight
						});
				}
			}

			return true;
		}

	private:
		std::unordered_map<Handler, TextureData> textures;
		std::unordered_map<Handler, std::vector<SDL_Rect>> frames;

	};
}

#endif
