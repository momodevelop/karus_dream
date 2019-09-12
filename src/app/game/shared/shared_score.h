#ifndef _APP_GAME_SHARED_SCORE_H__
#define _APP_GAME_SHARED_SCORE_H__

#include <entt.h>
#include "../shared/shared_textures.h"

namespace app::game::shared {
	class SharedScore {
		entt::registry& ecs;
		shared::SharedTextures& textures;

	public:
		SharedScore(entt::registry& ecs, shared::SharedTextures& textures);
		~SharedScore();

		void render(SDL_Renderer& renderer);

	};
}

#endif 