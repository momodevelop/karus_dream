#ifndef __YUU_SPRITESHEET_MANAGER_H__
#define __YUU_SPRITESHEET_MANAGER_H__

#include <SDL.h>
#include <yuu/utils.h>
#include <array>

namespace yuu {
	template<typename Handler>
	class SpritesheetManager {
	public:
		struct SpritesheetData {
			int rows, cols;
			std::vector<SDL_Rect> frames;
			const SDL_Rect& operator[](size_t index) const { return frames.at(index); }

			SpritesheetData(int rows, int cols)
				: rows(rows), cols(cols) {}
		};

	private:
		using container_t = std::unordered_map<Handler, SpritesheetData>;
		container_t spritesheets;
		
	public:

		inline const SpritesheetData operator[](Handler index) const {
			return spritesheets.at(index);
		}

		// http://jguegant.github.io/blogs/tech/performing-try-emplace.html
		bool load(Handler handler, int rows, int cols, int textureWidth, int textureHeight) {
			auto[itr, success] = spritesheets.try_emplace(handler, rows, cols);
			if (!success)
				return false;

			int tileWidth = textureWidth / cols;
			int tileHeight = textureHeight / rows;
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					int index = j + cols * i;
					itr->second.frames.emplace_back(SDL_Rect{
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
