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
#include "components/com_enemy.h"

#include "systems/sys_renderer.h"
#include "systems/sys_animation.h"
#include "systems/sys_player.h"
#include "systems/sys_collision.h"
#include "systems/sys_physics.h"
#include "systems/sys_ai.h"
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

	State::State(SDL_Renderer& renderer) :
		sharedSpawner(ecs, sharedAnimationIndices),
		sharedScore(ecs, sharedTextures)
	{
		if (!sharedKeyboard.init()) {
			assert(false); // throw instead?
		}

		if (!sharedAnimationIndices.init()) {
			assert(false);
		}

		auto font = TTF_OpenFont("img/arcade.ttf", 24);
		if (!font) {
			SDL_Log("Failed: %s\n", SDL_GetError());
			assert(false);
		}

		// init score
		char buffer[2] = " ";
		for (int i = 0; i < 10; ++i) {
			buffer[0] = '0' + i;
			if (!sharedTextures.addText(renderer, font, (TextureHandler)(ZERO + i), { 255, 255, 255 }, buffer)) {
				assert(false);
			}
		}

		if (!sharedTextures.addText(renderer, font, TEXT_SCORE, { 255, 255, 255 }, "Score: ") ||
			!sharedTextures.addText(renderer, font, TEXT_GAMEOVER, { 255, 255, 255 }, "Game Over: ") ||
			!sharedTextures.addText(renderer, font, TEXT_START, { 255, 255, 255 }, "Press Left or Right Arrow to start! ")) {
			assert(false);
		}


		// init textures
		if (!sharedTextures.addSpritesheet(renderer, KARU_SPRITESHEET,		"img/spritesheet_karu.png", 4, 3) ||
			!sharedTextures.addSpritesheet(renderer, GRID_SPRITESHEET,		"img/plains.png", 3, 5) ||
			!sharedTextures.addSpritesheet(renderer, BAT_SPRITESHEET,		"img/bat.png", 1, 3) ||
			!sharedTextures.addSpritesheet(renderer, SKELETON_SPRITESHEET,	"img/skeleton.png", 1, 4) ||
			!sharedTextures.addSpritesheet(renderer, FROG_SPRITESHEET,		"img/frog.png", 1, 3) ||
			!sharedTextures.addSpritesheet(renderer, GHOST_SPRITESHEET,		"img/ghost.png", 1, 3) ||
			!sharedTextures.addSpritesheet(renderer, COIN_SPRITESHEET,		"img/coin.png", 1, 6) ||
			!sharedTextures.addTexture(renderer, SWORD_TEXTURE, "img/sword.png"))
		{
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
			auto& indices = sharedAnimationIndices[SharedAnimationIndices::CHARACTER_STOP_DOWN];
			animation.indices.assign( indices.cbegin(), indices.cend());
			animation.speed = character::gAnimeSpeed;
			
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gTileSize, (float)gTileSize };
			
			auto& characterAnimation = ecs.assign<ComCharacterAnimation>(entity);
			characterAnimation.currentAnimeDir = characterAnimation.nextAnimeDir = SharedAnimationIndices::CHARACTER_STOP_DOWN;

			// jump trigger children
			for (int i = 0; i < 2; ++i)
			{
				auto entity = ecs.create();
				ecs.assign<ComTransform>(entity);
				ecs.assign<ComBoxCollider>(entity, AABB2f{ 0.f, 0.f, gJumpTriggerSize, gJumpTriggerSize });
				playerEntity.jumpTriggers[i] = entity;
			}

			// weapon child
			{
				auto entity = ecs.create();
				ecs.assign<ComTransform>(entity, Vec2f{ -100.f, -100.f }, Vec2f{ gWeaponTriggerWidth, gWeaponTriggerHeight });
				ecs.assign<ComBoxCollider>(entity, AABB2f{ 0.f, 0.f, gWeaponTriggerWidth, gWeaponTriggerHeight });
				auto& renderable = ecs.assign<ComRenderable>(entity);
				renderable.srcRect = {
					0, 0,
					sharedTextures[TextureHandler::SWORD_TEXTURE].width,
					sharedTextures[TextureHandler::SWORD_TEXTURE].height
				};
				renderable.textureHandler = TextureHandler::SWORD_TEXTURE;
				playerEntity.weaponTrigger = entity;
			}

			this->player = entity;
		}

		// floor
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{ 0.f , gDisplayHalfHeight }, Vec2f{ 0.f, 0.f });
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, (float)gDisplayWidth - 1, (float)gDisplayHalfHeight };
			ecs.assign<ComPlayerObstacle>(entity);
		}

		// left wall for player
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{-10.f, 0.f}, Vec2f{});
			ecs.assign<ComBoxCollider>(entity, ryoji::aabb::AABB2f{ 0.f, 0.f, float(10.f), float(gDisplayHeight) });
			ecs.assign<ComPlayerObstacle>(entity);


		}

		// right wall for player
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{ gDisplayWidth - 1, 0.f }, Vec2f{});
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			boxCollider.box = { 0.f, 0.f, float(10.f), float(gDisplayHeight) };
			ecs.assign<ComPlayerObstacle>(entity);
		}
		
		// test enemy
	


	}

	State::~State()
	{
	}

	void State::onEnter() noexcept
	{
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
		SysAi::updateEnemyAi(ecs, dt);
		SysCollision::resolvePlayerCollideObstacle(ecs, player);
		SysCollision::resolvePlayerCollideCollectible(ecs, player, sharedScore);
		SysCollision::resolvePlayerJumpTriggerCollision(ecs, player);
		SysCollision::resolveEnemyCollideWeapon(ecs, player, sharedScore);
		SysPlayer::updateTriggerPositions(ecs, player);

		// Animation
		SysAnimation::updateCharacterAnimationType(ecs, sharedAnimationIndices);
		SysAnimation::updateAnimation(ecs, sharedTextures, dt);

		

		sharedSpawner.update(dt);
		sharedKeyboard.clear();
	}

	void State::onExit() noexcept
	{
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{
		SysRenderer::renderBackground(renderer, sharedTextures);
		
#ifdef _DEBUG
		SysDebug::renderBoxColliders(ecs, renderer);
#endif
		SysRenderer::renderForeground(renderer, sharedTextures);
		SysRenderer::render(ecs, renderer, sharedTextures);
		SysRenderer::renderStartGameOver(ecs, renderer, sharedTextures, player);
		sharedScore.render(renderer);

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
