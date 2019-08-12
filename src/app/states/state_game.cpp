#include <SDL.h>
#include <SDL_image.h>
#include <constants.h>
#include <ryoji/vector.h>

#include "../root.h"

#include "state_game.h"


#include "../game/systems/sys_renderer.h"
#include "../game/systems/sys_animator.h"

#include "../game/components/com_renderable.h"
#include "../game/components/com_transform.h"
#include "../game/components/com_animation.h"



#include "../game/player_controller.h"


namespace app {

	using namespace game;
	using namespace ryoji;
	using namespace math;
	using namespace components;

	StateGame::StateGame(SDL_Renderer& renderer)
	{


		textureShelf.loadFromPath(&renderer, TEXTURE_KARU_SPRITESHEET, "img/spritesheet_karu.png");
		textureShelf.loadFromPath(&renderer, TEXTURE_GRID_SPRITESHEET, "img/tiles.jpg");

		tileList.resize(100);

		// initialize tiles
		for (int i = 0; i < 100; ++i) {
			tileList[i].type = (Tile::Type)(i % Tile::MAX);
		}


		// initialize entities
		for (int i = 0; i < kMaxEntities; ++i) {
			using namespace character;
			
			auto entity = ecs.create();
			
			Vec2f position = { 10.f * i, 200.f };
			Vec2f scale = { kSize, kSize };
			ecs.assign<ComTransform>(entity, position, scale);
			
			auto& renderable = ecs.assign<ComRenderable>(entity);
			renderable.texture = textureShelf[TEXTURE_KARU_SPRITESHEET];

			auto& animation = ecs.assign<ComAnimation>(entity);
			animation.indices.reserve(kAnimeMaxFrames);
			animation.indices.assign(kAnimeIndices[ANIME_FRONT], kAnimeIndices[ANIME_FRONT] + kAnimeMaxFrames);
			animation.speed = kAnimeSpeed;
		}
		
	}

	StateGame::~StateGame()
	{
	}

	void StateGame::onEnter() noexcept
	{
		SDL_Log("game::StateGame::onEnter()");

	}

	void StateGame::onUpdate(float dt) noexcept
	{
		sysAnimator.update(ecs, dt);
	}

	void StateGame::onExit() noexcept
	{
		SDL_Log("game::StateGame::onExit()");
	}

	void StateGame::onRender(SDL_Renderer& renderer) noexcept
	{
		sysRenderer.render(ecs, renderer);
	}

	void StateGame::onHandleEvent(SDL_Event& e) noexcept
	{
		//playerController->handleInput(e);
	}

	void StateGame::onClean() noexcept
	{
	}



}