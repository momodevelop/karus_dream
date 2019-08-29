#include <SDL.h>
#include <SDL_image.h>
#include <constants.h>
#include <ryoji/vector.h>

#include "../root.h"

#include "state.h"

#include "components/com_renderable.h"
#include "components/com_transform.h"
#include "components/com_animation.h"
#include "components/com_player.h"
#include "components/com_character_animation.h"
#include "components/com_box_collider.h"
#include "components/com_obstacle.h"
#include "components/com_rigidbody.h"

#include "systems/sys_renderer.h"
#include "systems/sys_animation.h"
#include "systems/sys_input.h"
#include "systems/sys_collision.h"
#include "systems/sys_physics.h"
#include "systems/sys_debug.h"



namespace app::game {

	using namespace ryoji;
	using namespace math;
	using namespace components;
	using namespace shared;
	using namespace yuu;
	using namespace systems;

	State::State(SDL_Renderer& renderer)
	{
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

			ecs.assign<ComPlayer>(entity);

			Vec2f position = { 10.f , 200.f };
			Vec2f scale = { gTileSize, gTileSize };
			ecs.assign<ComTransform>(entity, position, scale);
			ecs.assign<ComRigidBody>(entity);

			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.textureHandler = SharedTextures::KARU_SPRITESHEET;

			auto& animation = ecs.assign<ComAnimation>(entity);
			auto& indices = sharedCharacterAnimations[SharedCharacterAnimations::STOP_DOWN];
			animation.indices.assign( indices.cbegin(), indices.cend());
			animation.speed = gAnimeSpeed;
			
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gTileSize, (float)gTileSize };
			
			auto& characterAnimation = ecs.assign<ComCharacterAnimation>(entity);
			characterAnimation.currentAnimeDir = characterAnimation.nextAnimeDir = SharedCharacterAnimations::STOP_DOWN;
		}

		{
			using namespace character;
			auto entity = ecs.create();
			
			Vec2f position = { 200.f , 200.f };
			Vec2f scale = { gTileSize, gTileSize };
			ecs.assign<ComTransform>(entity, position, scale);

		//	auto& renderable = ecs.assign<ComRenderable>(entity);
		//	renderable.texture = SharedTextures::KARU_SPRITESHEET;

			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gTileSize, (float)gTileSize };

			ecs.assign<ComObstacle>(entity);


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
		// Input
		SysInput::update(ecs, sharedKeyboard);
		
		// Physics
		SysPhysics::update(ecs, dt);
		SysCollision::resolvePlayerCollideObstacle(ecs);

		// Rendering
		SysAnimation::updateCharacterAnimationType(ecs, sharedCharacterAnimations);
		SysAnimation::updateAnimation(ecs, sharedTextures, dt);
		
	}

	void State::onExit() noexcept
	{
		SDL_Log("game::State::onExit()");
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{
		SysRenderer::render(ecs, renderer, sharedTextures);
#ifdef _DEBUG
		SysDebug::renderBoxColliders(ecs, renderer);
#endif
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
	}

	void State::onHandleEvent(SDL_Event& e) noexcept
	{
		
		sharedKeyboard.handleEvent(e);
	}

	void State::onClean() noexcept
	{
	}



}