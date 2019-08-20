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
#include "components/com_character_animation.h"


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

		if (!sharedKeyboard.init()) {
			assert(false); // throw instead?
		}

		if (!sharedCharacterAnimations.init()) {
			assert(false);
		}

		// initialize main character
		{	
			using namespace character;

			auto entity = ecs.create();

			Vec2f position = { 10.f , 200.f };
			Vec2f scale = { kSize, kSize };
			ecs.assign<ComTransform>(entity, position, scale);

			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.texture = SharedTextures::KARU_SPRITESHEET;

			auto& animation = ecs.assign<ComAnimation>(entity);
			auto& indices = sharedCharacterAnimations[SharedCharacterAnimations::STOP_DOWN];
			animation.indices.assign( indices.cbegin(), indices.cend());
			animation.speed = kAnimeSpeed;

			ecs.assign<ComPlayerInput>(entity);
			
			auto& characterAnimation = ecs.assign<ComCharacterAnimation>(entity);
			characterAnimation.currentAnimeDir = characterAnimation.nextAnimeDir = SharedCharacterAnimations::STOP_DOWN;

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
		sysPlayerInput.update(ecs, sharedKeyboard, dt);
		sysCharacterAnimator.update(ecs, sharedCharacterAnimations);
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
		
		sharedKeyboard.handleEvent(e);
	}

	void State::onClean() noexcept
	{
	}



}