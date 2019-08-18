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

		bool init(SDL_Renderer&);

		inline yuu::SDL_TextureUniquePtr& operator[](Handler index) {
			return textures[index];
		}

		inline const yuu::SDL_TextureUniquePtr& operator[](Handler index) const {
			return textures[index];
		}

	private:

		std::array<yuu::SDL_TextureUniquePtr, MAX> textures;

	};
}

#endif
