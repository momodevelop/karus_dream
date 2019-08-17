#include <SDL.h>
#include <SDL_image.h>
#include <constants.h>
#include <ryoji/vector.h>

#include "../root.h"

#include "state.h"

#include "components/com_renderable.h"
#include "components/com_transform.h"
#include "components/com_animation.h"
#include "components/com_player_input.h"


namespace app::game {

	using namespace ryoji;
	using namespace math;
	using namespace components;
	using namespace shared;
	using namespace yuu;

	State::State(SDL_Renderer& renderer)
	{
		// init textures
		if (!sharedTextures.init(renderer)) {
			assert(false); // throw instead?
		}


		// initialize entities
		{	
			using namespace character;

			auto entity = ecs.create();

			Vec2f position = { 10.f , 200.f };
			Vec2f scale = { kSize, kSize };
			ecs.assign<ComTransform>(entity, position, scale);

			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.texture = SharedTextures::KARU_SPRITESHEET;

			auto& animation = ecs.assign<ComAnimation>(entity);
			animation.indices.reserve(kAnimeMaxFrames);
			animation.indices.assign(kAnimeIndices[ANIME_FRONT], kAnimeIndices[ANIME_FRONT] + kAnimeMaxFrames);
			animation.speed = kAnimeSpeed;

		}
		
	}

	State::~State()
	{
	}

	void State::onEnter() noexcept
	{
		SDL_Log("game::State::onEnter()");

	}

	void State::onUpdate(float dt) noexcept
	{
		sysAnimator.update(ecs, dt);
	}

	void State::onExit() noexcept
	{
		SDL_Log("game::State::onExit()");
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{
		sysRenderer.render(ecs, renderer, sharedTextures);
	}

	void State::onHandleEvent(SDL_Event& e) noexcept
	{
		sysInput.handleEvent(ecs, e);
	}

	void State::onClean() noexcept
	{
	}



}