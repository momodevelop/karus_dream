
#include <entt.h>
#include <SDL.h>


#include <constants.h>
#include <ryoji/vector.h>

#include "../components/com_transform.h"
#include "../components/com_player.h"
#include "../components/com_animation.h"
#include "../components/com_character_animation.h"
#include "../components/com_rigidbody.h"

#include "../shared/shared_keyboard.h"
#include "../shared/shared_character_animations.h"

#include "sys_input.h"

#define SPEED 250.f
#define JUMP 500.f

namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;
	using namespace shared;


	void SysInput::update(entt::registry& registry, SharedKeyboard& sharedKeyboard) {
		using namespace character;
		
		using SharedAnime = SharedCharacterAnimations; // so that I don't have to type lol

		auto view = registry.view<ComRigidBody, ComPlayer, ComCharacterAnimation>();
		for (auto entity : view) {
			Vec2f direction { 0.f, 0.f };

			auto& rigidbody = view.get<ComRigidBody>(entity);
			auto& characterAnimation = view.get<ComCharacterAnimation>(entity);
			

			// movement
			if (sharedKeyboard.isKeyDown(SharedKeyboard::LEFT)) {
				rigidbody.velocity.x = -SPEED;
				characterAnimation.nextAnimeDir = SharedAnime::NORM_LEFT;
			}
			else if (sharedKeyboard.isKeyDown(SharedKeyboard::RIGHT)) {
				rigidbody.velocity.x = SPEED;
				characterAnimation.nextAnimeDir = SharedAnime::NORM_RIGHT;
			}	

			if (sharedKeyboard.isKeyDown(SharedKeyboard::UP)) {
				rigidbody.velocity.y = -JUMP;
			}

		}

	}

}