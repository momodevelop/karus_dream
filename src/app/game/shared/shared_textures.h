#ifndef __APP_GAME_SHARED_TEXTURES_H__
#define __APP_GAME_SHARED_TEXTURES_H__


#include <yuu/texture_manager.h>
#include "../types.h"

namespace app::game::shared {
	/*class SharedTextures {
	public:
		enum Handler {
			KARU_SPRITESHEET,
			GRID_SPRITESHEET,
			MAX
		};

		struct TextureData {
			yuu::SDL_TextureUniquePtr texture;
			Handler handler;
			int width, height;
			int rows, cols;
		};

	public:

		bool init(SDL_Renderer&);

		inline TextureData& operator[](Handler index) {
			return textures[index];
		}

		inline const TextureData& operator[](Handler index) const {
			return textures[index];
		}

		inline const SDL_Rect& getFrame(Handler index, size_t frameIndex) const {
			return frames[index][frameIndex];
		}

	private:
		bool initTextureData(SDL_Renderer& renderer, SharedTextures::Handler handler, const char * path, int width, int height, int rows, int cols);
		std::array<TextureData, MAX> textures;
		std::array<std::vector<SDL_Rect>, MAX> frames;

	};*/

	using SharedTextures = yuu::TextureManager<TextureHandler>;
}

#endif
