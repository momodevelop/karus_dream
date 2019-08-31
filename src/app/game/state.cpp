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
#include "components/com_constant_force.h"
#include "components/com_collectible.h"

#include "systems/sys_renderer.h"
#include "systems/sys_animation.h"
#include "systems/sys_player.h"
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


	void State::reset()
	{
	}

	State::State(SDL_Renderer& renderer)
	{
	

		if (!sharedKeyboard.init()) {
			assert(false); // throw instead?
		}

		if (!sharedCharacterAnimations.init()) {
			assert(false);
		}

		// init textures
		
		if (!sharedTextures.addTexture(renderer, KARU_SPRITESHEET, "img/spritesheet_karu.png", 144, 192, 4, 3) ||
			!sharedTextures.addTexture(renderer, GRID_SPRITESHEET, "img/plains.png", 80, 48, 3, 5)) {
			assert(false);
		}


		// initialize main character
		{	
			using namespace ryoji::aabb;
			auto entity = ecs.create();

			auto& playerEntity = ecs.assign<ComPlayer>(entity);

			Vec2f position = { float(gDisplayHalfWidth - gHalfTileSize), gSpawnableHeight };
			Vec2f scale = { gTileSize, gTileSize };
			ecs.assign<ComTransform>(entity, position, scale);
			ecs.assign<ComRigidBody>(entity);
			ecs.assign<ComConstantForce>(entity, Vec2f{ 0.f, 2000.f });
			
			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.textureHandler = TextureHandler::KARU_SPRITESHEET;

			auto& animation = ecs.assign<ComAnimation>(entity);
			auto& indices = sharedCharacterAnimations[SharedCharacterAnimations::STOP_DOWN];
			animation.indices.assign( indices.cbegin(), indices.cend());
			animation.speed = character::gAnimeSpeed;
			
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gTileSize, (float)gTileSize };
			
			auto& characterAnimation = ecs.assign<ComCharacterAnimation>(entity);
			characterAnimation.currentAnimeDir = characterAnimation.nextAnimeDir = SharedCharacterAnimations::STOP_DOWN;

			// jump trigger children
			for (int i = 0; i < 2; ++i)
			{
				auto entity = ecs.create();
				ecs.assign<ComTransform>(entity);
				ecs.assign<ComBoxCollider>(entity, AABB2f{ 0.f, 0.f, gJumpTriggerSize, gJumpTriggerSize });
				playerEntity.jumpTriggers[i] = entity;
			}

			this->player = entity;
		}

		// floor
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{ 0.f , gDisplayHalfHeight }, Vec2f{ 0.f, 0.f });
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gDisplayWidth - 1, (float)gDisplayHalfHeight };
			ecs.assign<ComObstacle>(entity);
		}

		// left wall for player
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{-10.f, 0.f}, Vec2f{});
			ecs.assign<ComBoxCollider>(entity, ryoji::aabb::AABB2f{ 0.f, 0.f, float(10.f), float(gDisplayHeight) });
			ecs.assign<ComObstacle>(entity);
		}

		// right wall for player
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{ gDisplayWidth - 1, 0.f }, Vec2f{});
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, float(10.f), float(gDisplayHeight) };
			ecs.assign<ComObstacle>(entity);
		}
		

		// Test for collectible
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{10.f, gSpawnableHeight }, Vec2f{});
			ecs.assign<ComCollectible>(entity);
			ecs.assign<ComBoxCollider>(entity, ryoji::aabb::AABB2f{ 0.f, 0.f, float(gTileSize), float(gTileSize) });

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
		SysPlayer::processInput(ecs, sharedKeyboard, player);
		
		// update player variables
		SysPlayer::update(ecs, player, dt);

		// Physics 
		SysPhysics::updateConstantForces(ecs);
		SysPhysics::updateMovement(ecs, 1/60.f); //fixed time step for physics
		SysCollision::resolvePlayerCollideObstacle(ecs, player);
		SysCollision::resolvePlayerCollideCollectible(ecs, player);
		SysCollision::resolvePlayerJumpTriggerCollision(ecs, player);
		SysPlayer::updateJumpTriggerPosition(ecs, player);

		// Animation
		SysAnimation::updateCharacterAnimationType(ecs, sharedCharacterAnimations);
		SysAnimation::updateAnimation(ecs, sharedTextures, dt);
	}

	void State::onExit() noexcept
	{
		SDL_Log("game::State::onExit()");
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{
		SysRenderer::renderBackground(renderer, sharedTextures);
		SysRenderer::render(ecs, renderer, sharedTextures);
#ifdef _DEBUG
		SysDebug::renderBoxColliders(ecs, renderer);
#endif
		SysRenderer::renderForeground(renderer, sharedTextures);
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
