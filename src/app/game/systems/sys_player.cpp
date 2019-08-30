
#include <entt.h>
#include <SDL.h>


#include <constants.h>
#include <ryoji/vector.h>

#include "../components/com_transform.h"
#include "../components/com_player.h"
#include "../components/com_animation.h"
#include "../components/com_character_animation.h"
#include "../components/com_rigidbody.h"
#include "../components/com_player_jump_trigger.h"
#include "../components/com_box_collider.h"

#include "../shared/shared_keyboard.h"
#include "../shared/shared_character_animations.h"

#include "sys_player.h"

#define SPEED 250.f
#define JUMP 500.f

namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;
	using namespace shared;


	void SysPlayer::updateJumpTriggerPosition(entt::registry & ecs)
	{
		// there's really only 1 of each..
		using namespace character;
		auto players = ecs.view<ComPlayer, ComBoxCollider, ComTransform>();
		auto triggers = ecs.view<ComPlayerJumpTrigger, ComTransform>();
		for (auto player : players) {
			for (auto trigger : triggers) {
				// put it below the player
				auto& playerTransform = players.get<ComTransform>(player);
				auto& playerRb = players.get<ComBoxCollider>(player);
				auto& triggerTransform = triggers.get<ComTransform>(trigger);

				triggerTransform.position = playerTransform.position + ryoji::math::Vec2f{0.f, };

			}
		}
	}

	void SysPlayer::processInput(entt::registry& registry, SharedKeyboard& sharedKeyboard) {
		using namespace character;
		
		using SharedAnime = SharedCharacterAnimations; // so that I don't have to type lol

		auto view = registry.view<ComRigidBody, ComPlayer, ComCharacterAnimation>();
		for (auto entity : view) {
			Vec2f direction { 0.f, 0.f };

			auto& rigidbody = view.get<ComRigidBody>(entity);
			auto& characterAnimation = view.get<ComCharacterAnimation>(entity);
			auto& player = view.get<ComPlayer>(entity);

			// movement
			if (sharedKeyboard.isKeyDown(SharedKeyboard::LEFT)) {
				rigidbody.velocity.x = -SPEED;
				characterAnimation.nextAnimeDir = SharedAnime::NORM_LEFT;
			}
			else if (sharedKeyboard.isKeyDown(SharedKeyboard::RIGHT)) {
				rigidbody.velocity.x = SPEED;
				characterAnimation.nextAnimeDir = SharedAnime::NORM_RIGHT;
			}	

			if (sharedKeyboard.isKeyDown(SharedKeyboard::UP) && player.canJump) {
				rigidbody.velocity.y = -JUMP;
			}

		}

	}

}