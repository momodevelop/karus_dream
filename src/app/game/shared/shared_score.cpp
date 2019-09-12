
#include "../components/com_transform.h"
#include "../components/com_renderable.h"
#include "../components/com_box_collider.h"
#include "../components/com_animation.h"
#include "../components/com_collectible.h"


#include <constants.h>
#include "shared_score.h"

namespace app::game::shared {
	using namespace components;
	using namespace ryoji::math;
	using namespace shared;

	SharedScore::SharedScore(entt::registry& ecs, SharedTextures& textures)
		: textures(textures), ecs(ecs)
	{

	}
	SharedScore::~SharedScore()
	{
	}

	void SharedScore::render(SDL_Renderer& renderer)
	{

	}
	
	
}

