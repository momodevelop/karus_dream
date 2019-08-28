#ifndef __APP_GAME_SYSTEMS_GRID_RENDERER_H__
#define __APP_GAME_SYSTEMS_GRID_RENDERER_H__

#include <SDL.h>

#include "../shared/shared_grid.h"
#include "../shared/shared_textures.h"

namespace app::game::systems {

	class SysGridRenderer {
	public:
		void render(SDL_Renderer& renderer, shared::SharedGrid& sharedGrid, shared::SharedTextures& sharedTextures);
	};
}


#endif