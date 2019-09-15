#ifndef _APP_GAME_SHARED_SCORE_H__
#define _APP_GAME_SHARED_SCORE_H__

#include <entt.h>
#include <string>
#include "../shared/shared_textures.h"

namespace app::game::shared {
	class SharedScore {
	private:

		static constexpr unsigned kMaxScore = 9999;
		static constexpr unsigned kScorePlaces = 4;

	private:
		std::array<uint8_t, kScorePlaces> scoreStr;
		entt::registry& ecs;
		shared::SharedTextures& textures;
		unsigned score;
		
		void renderTextAt(SDL_Renderer & renderer, TextureHandler handler, int x, int y, float scale);
		void syncScoreToScoreStr();
	public:
		SharedScore(entt::registry& ecs, shared::SharedTextures& textures);
		~SharedScore();

		void render(SDL_Renderer& renderer);
		void addScore(unsigned int i);

	};
}

#endif 