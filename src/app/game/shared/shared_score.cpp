
#include <string>

#include "../components/com_transform.h"
#include "../components/com_renderable.h"
#include "../components/com_box_collider.h"
#include "../components/com_animation.h"
#include "../components/com_collectible.h"

#include "../../types.h"

#include <constants.h>
#include <ryoji/common.h>

#include "shared_score.h"


using namespace std;

namespace app::game::shared {
	using namespace components;
	using namespace ryoji::math;
	using namespace shared;


	SharedScore::SharedScore(entt::registry& ecs, SharedTextures& textures)
		: textures(textures), ecs(ecs)
	{
		addScore(0);
	}
	SharedScore::~SharedScore()
	{
	}

	void SharedScore::render(SDL_Renderer& renderer)
	{
		int y = gDisplayHeight - 22;
		renderTextAt(renderer, TEXT_SCORE, 10, y, 0.9f);

		// Render score based on scoreStr
		int x = 90;
		for (auto& c : scoreStr) {
			renderTextAt(renderer, TextureHandler(ZERO + c), x += 15, y, 0.9f);
		}
		
	}

	void SharedScore::renderFinalScore(SDL_Renderer & renderer)
	{
		int x = gDisplayHalfWidth - 80;
		int y = gDisplayHalfHeight - 15;
		renderTextAt(renderer, TEXT_SCORE_B, x, y, 0.9f);

		x += 80;

		// Render score based on scoreStr
		for (auto& c : scoreStr) {
			renderTextAt(renderer, TextureHandler(ZERO_B + c), x += 15, y, 0.9f);
		}
	}

	void SharedScore::addScore(unsigned int i)
	{
		score += i;
		if (score > kMaxScore)
			score = kMaxScore;
		
		syncScoreToScoreStr();
	}
	
	void SharedScore::renderTextAt(SDL_Renderer & renderer, TextureHandler handler, int x, int y, float scale)
	{
		int w, h;
		SDL_QueryTexture(textures[handler].texture.get(), 0, 0, &w, &h);
		SDL_Rect destRec = { x, y, int(w * scale), int(h * scale) };
		SDL_RenderCopy(&renderer, textures[handler].texture.get(), nullptr, &destRec);
	}

	void SharedScore::syncScoreToScoreStr()
	{
		assert(score <= kMaxScore);
		// I'm lazy to write an algo
		unsigned tempScore = score;
		unsigned divider = pow(10U, kScorePlaces - 1);
		
		for (auto& c : scoreStr) {
			unsigned subtract = tempScore / divider;
			c = subtract;
			tempScore -= subtract * divider;
			divider /= 10;
		}
		
	}


}

