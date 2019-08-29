#ifndef __APP_STATE_GAME_H__
#define __APP_STATE_GAME_H__

#include <bitset>

#include <SDL.h>
#include <constants.h>
#include <entt.h>
#include <yuu/utils.h>

#include "types.h"

#include "shared/shared_textures.h"
#include "shared/shared_keyboard.h"
#include "shared/shared_character_animations.h"

#include "../state_base.h"



namespace app::game {
	// Forward declarations
	class Root;
	class State : public StateBase {
		constexpr static int kMaxEntities = 10;
	private:
		entt::registry ecs;


		shared::SharedTextures sharedTextures;
		shared::SharedKeyboard sharedKeyboard;
		shared::SharedCharacterAnimations sharedCharacterAnimations;
		

	private:
		State(const State&) = delete;
		State& operator=(const State&) = delete;
		
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