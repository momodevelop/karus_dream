#ifndef __YUU_TEXTURE_MANAGER_H__
#define __YUU_TEXTURE_MANAGER_H__

#include <SDL.h>
#include <yuu/utils.h>
#include <array>

namespace yuu {
	template<typename Handler>
	class SpritesheetManager {
		std::unordered_map<Handler, SpritesheetData> spritesheetDatas;

	public:
		class SpritesheetData {
			friend class SpritesheetManager;
		private:
			std::vector<SDL_Rect> frames;
			size_t rows, cols;
		public:
			inline size_t getRows() { return rows; }
			inline size_t getCols() { return cols; }

			const SDL_Rect& operator[](size_t index) { return frames[index]; }
		};
		
	public:
		inline SpritesheetData& operator[](Handler index) {
			return spritesheetDatas[index];
		}

		inline const SpritesheetData& operator[](Handler index) const {
			return spritesheetDatas[index];
		}

		bool load(SDL_Renderer& renderer, Handler handler, const char * path, int rows, int cols)
		{
			if (!addTexture(renderer, handler, path)) {
				return false;
			}
			auto& textureData = textures[handler];
			return addSpritesheetData(handler, textureData.width, textureData.height, rows, cols);

		}

		bool load(SDL_Renderer& renderer, Handler handler, SDL_Surface * surface, int rows, int cols) {
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
		

	};
}

#endif
