#include <SDL.h>
#include <SDL_image.h>
#include <constants.h>
#include <ryoji/vector.h>
#include <ryoji/easing.h>

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

	State::State(SDL_Renderer& renderer, std::function<void()> completedCallback) :
		sharedSpawner(ecs, sharedAnimationIndices),
		sharedScore(ecs, sharedTextures),
		completedCallback(completedCallback)
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
			if (!sharedTextures.addText(renderer, font, (TextureHandler)(ZERO_B + i), { 0, 0, 0 }, buffer)) {
				assert(false);
			}
		}

		if (!sharedTextures.addText(renderer, font, TEXT_SCORE, { 255, 255, 255 }, "Score: ") ||
			!sharedTextures.addText(renderer, font, TEXT_SCORE_B, { 0, 0, 0 }, "Score: ") ||
			!sharedTextures.addText(renderer, font, TEXT_GAMEOVER, { 0, 0, 0 }, "Game Over: Press Z to restart.") ||
			!sharedTextures.addText(renderer, font, TEXT_START, { 255, 255, 255 }, "Press Left or Right Arrow to start! ")) {
			assert(false);
		}


		// init textures
		if (!sharedTextures.addTexture(renderer, BLANK_TEXTURE,		"img/blank.png") ||
			!sharedTextures.addTexture(renderer, KARU_TEXTURE,		"img/spritesheet_karu.png") ||
			!sharedTextures.addTexture(renderer, GRID_TEXTURE,		"img/plains.png") ||
			!sharedTextures.addTexture(renderer, TEXTURE_BAT,		"img/bat.png") ||
			!sharedTextures.addTexture(renderer, TEXTURE_SKELETON,	"img/skeleton.png") ||
			!sharedTextures.addTexture(renderer, FROG_TEXTURE,		"img/frog.png") ||
			!sharedTextures.addTexture(renderer, TEXTURE_GHOST,		"img/ghost.png") ||
			!sharedTextures.addTexture(renderer, COIN_TEXTURE,		"img/coin.png") ||
			!sharedTextures.addTexture(renderer, SWORD_TEXTURE,		"img/sword.png"))
		{
			assert(false);
		}

		// init spritesheets
		if (!sharedSpritesheets.load(KARU_SPRITESHEET,		4, 3,	sharedTextures[KARU_TEXTURE].width, sharedTextures[KARU_TEXTURE].height) ||
			!sharedSpritesheets.load(GRID_SPRITESHEET,		3, 5,	sharedTextures[GRID_TEXTURE].width, sharedTextures[GRID_TEXTURE].height) ||
			!sharedSpritesheets.load(SPRITESHEET_BAT,		1, 3,	sharedTextures[TEXTURE_BAT].width, sharedTextures[TEXTURE_BAT].height) ||
			!sharedSpritesheets.load(SPRITESHEET_SKELETON,	1, 4,	sharedTextures[TEXTURE_SKELETON].width, sharedTextures[TEXTURE_SKELETON].height) ||
			!sharedSpritesheets.load(SPRITESHEET_FROG,		1, 3,	sharedTextures[FROG_TEXTURE].width, sharedTextures[FROG_TEXTURE].height) ||
			!sharedSpritesheets.load(SPRITESHEET_GHOST,		1, 3,	sharedTextures[TEXTURE_GHOST].width, sharedTextures[TEXTURE_GHOST].height) ||
			!sharedSpritesheets.load(COIN_SPRITESHEET,		1, 6,	sharedTextures[COIN_TEXTURE].width, sharedTextures[COIN_TEXTURE].height))
		{
			assert(false);
		}


		// game over
		{
			auto entity = ecs.create();
			ecs.assign<ComTransform>(entity, Vec2f{ 0.f, 0.f }, Vec2f{ gDisplayWidth, gDisplayHeight });
			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.textureHandler = TextureHandler::BLANK_TEXTURE;
			SDL_QueryTexture(sharedTextures[TextureHandler::BLANK_TEXTURE].texture.get(), 0, 0, &renderable.srcRect.w, &renderable.srcRect.h);
			renderable.alpha = 0;

			this->fadeOutEntity = entity;
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
			renderable.textureHandler = TextureHandler::KARU_TEXTURE;

			auto& animation = ecs.assign<ComAnimation>(entity);
			auto& indices = sharedAnimationIndices[SharedAnimationIndices::CHARACTER_STOP_DOWN];
			animation.indices.assign( indices.cbegin(), indices.cend());
			animation.speed = character::gAnimeSpeed;
			
			auto& boxCollider = ecs.assign<ComBoxCollider>(entity);
			float offset = 5.f;
			boxCollider.box = { offset, 0.f, (float)gTileSize - offset, (float)gTileSize };
			
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
		



	}

	State::~State()
	{
	}

	void State::onEnter() noexcept
	{
	}

	void State::onUpdate(float dt) noexcept
	{
		// hack
		dt = 1 / 60.f;


		if (sharedGameState.state == SharedGameState::GAME_UPDATE || sharedGameState.state == SharedGameState::GAME_START) {
			// Input
			SysPlayer::processInput(ecs, sharedKeyboard, player, sharedGameState);

			// update player variables
			SysPlayer::update(ecs, player, dt);

			// Physics 
			SysPhysics::updateConstantForces(ecs);
			SysPhysics::updateMovement(ecs, dt); //fixed time step for physics?
			SysPlayer::updateTriggerPositions(ecs, player);
			SysAi::updateEnemyAi(ecs, dt);
			SysCollision::resolvePlayerCollideObstacle(ecs, player);
			SysCollision::resolvePlayerCollideCollectible(ecs, player, sharedScore);
			SysCollision::resolvePlayerJumpTriggerCollision(ecs, player);
			SysCollision::resolveEnemyCollideWeapon(ecs, player, sharedScore);
			SysCollision::resolvePlayerCollideEnemy(ecs, player, sharedGameState);
			

			// Animation
			SysAnimation::updateCharacterAnimationType(ecs, sharedAnimationIndices);
			SysAnimation::updateAnimation(ecs, sharedTextures, sharedSpritesheets, dt);
			
			// Enemy spawning logic 
			if (sharedGameState.state == SharedGameState::GAME_UPDATE)
				sharedSpawner.update(dt);
		}
		
		else if (sharedGameState.state == SharedGameState::GAME_OVER) {
			using namespace components;
			// do game over
			auto* renderer = ecs.try_get<ComRenderable>(fadeOutEntity);
			if (renderer) {
				fadeOutTimer += dt;
				if (fadeOutTimer > fadeOutDuration) {
					fadeOutTimer = fadeOutDuration;
					sharedGameState.state = shared::SharedGameState::GAME_OVER_DONE;
				}

				renderer->alpha = ryoji::easing::ease(0, 255, fadeOutTimer / fadeOutDuration);
			}


		}
		else if (sharedGameState.state == SharedGameState::GAME_OVER_DONE) {
			if (sharedKeyboard.isKeyDown(SharedKeyboard::Z)) {
				completedCallback();
			}
		}
		sharedKeyboard.clear();
	}

	void State::onExit() noexcept
	{
	}

	void State::onRender(SDL_Renderer& renderer) noexcept
	{
		SysRenderer::renderBackground(renderer, sharedTextures, sharedSpritesheets);
		

//		SysDebug::renderBoxColliders(ecs, renderer);

		SysRenderer::renderForeground(renderer, sharedTextures, sharedSpritesheets);
		SysRenderer::render(ecs, renderer, sharedTextures);
		
		if (sharedGameState.state == SharedGameState::GAME_START)
			SysRenderer::renderStart(ecs, renderer, sharedTextures);
		else if (sharedGameState.state == SharedGameState::GAME_OVER_DONE) {
			SysRenderer::renderGameOver(ecs, renderer, sharedTextures);
			sharedScore.renderFinalScore(renderer);
		}
		else {
			sharedScore.render(renderer);
		}
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
