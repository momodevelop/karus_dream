#ifndef __APP_GAME_SHARED_TEXTURES_H__
#define __APP_GAME_SHARED_TEXTURES_H__

#include <SDL.h>
#include <yuu/utils.h>
#include <array>

namespace app::game::shared {
	class SharedTextures {
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

	private:
		bool initTextureData(SDL_Renderer& renderer, SharedTextures::Handler handler, const char * path, int width, int height, int rows, int cols);
		std::array<TextureData, MAX> textures;

	};
}

#endif
