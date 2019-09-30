#ifndef __APP_STATE_GAME_H__
#define __APP_STATE_GAME_H__

#include <bitset>

#include <SDL.h>
#include <constants.h>
#include <entt.h>
#include <yuu/utils.h>
#include <yuu/texture_manager.h>

#include "types.h"

#include "shared/shared_textures.h"
#include "shared/shared_keyboard.h"
#include "shared/shared_animation_indices.h"
#include "shared/shared_spawner.h"
#include "shared/shared_score.h"

#include "../state_base.h"



namespace app::game {
	// Forward declarations
	class Root;
	class State : public StateBase {
		constexpr static int kMaxEntities = 10;
	private:
		enum States {
			START,
			PLAY,
			END
		} state{ START };

		entt::registry ecs;
		entt::entity player;

		//shared::SharedTextures sharedTextures;

		shared::SharedTextures sharedTextures;
		shared::SharedKeyboard sharedKeyboard;
		shared::SharedAnimationIndices sharedAnimationIndices;
		shared::SharedSpawner sharedSpawner;
		shared::SharedScore sharedScore;

	private:
		State(const State&) = delete;
		State& operator=(const State&) = delete;

		void reset();
		void renderTextAt(SDL_Renderer & renderer, TextureHandler handler, int x, int y, float scale);
		
	public:
		State(SDL_Renderer& renderer);
		~State();

		virtual void onEnter() noexcept override;
		virtual void onUpdate(float dt) noexcept override;
		virtual void onExit() noexcept override;
		virtual void onRender(SDL_Renderer& renderer) noexcept override;
		virtual void onHandleEvent(SDL_Event& e) noexcept override;
		virtual void onClean() noexcept override; 

	};


}
#endif