#include "shared_textures.h"

using namespace yuu;

namespace app::game::shared {
	struct Data {
		SharedTextures::Handler index;
		const char * path;
	};

	static constexpr std::array<Data, SharedTextures::MAX> datas = {
		Data{ SharedTextures::KARU_SPRITESHEET, "img/spritesheet_karu.png" },
		Data{ SharedTextures::GRID_SPRITESHEET, "img/tiles.jpg" }
	};


	bool SharedTextures::init(SDL_Renderer& renderer)
	{
		for (const auto& data : datas) {
			textures[data.index] = SDL_TextureUniquePtr(yuu::SDL_CreateTextureFromPathX(&renderer, data.path));
			if (!textures[data.index])
				return false;			
		}

		return true;

	}
}