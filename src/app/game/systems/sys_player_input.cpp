#include <constants.h>
#include <ryoji/vector.h>

#include "../components/com_transform.h"
#include "../components/com_player_input.h"
#include "../components/com_animation.h"
#include "../components/com_character_animation.h"

#include "../shared/shared_character_animations.h"

#include "sys_player_input.h"

#define SPEED 250.f

namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;
	
	void doMovement(ComTransform& transform, Vec2f& velocity, float dt) {
		auto normVelocity = normalize(velocity);
		if (normVelocity.has_value())
			transform.position += normVelocity.value() * SPEED * dt;
	}

	void SysPlayerInput::update(entt::registry& registry, SharedKeyboard& sharedKeyboard, float dt) {
		using namespace character;
		using namespace shared;

		auto view = registry.view<ComTransform, ComPlayerInput, ComAnimation, ComCharacterAnimation>();
		for (auto entity : view) {
			Vec2f velocity { 0.f, 0.f };
			

			auto& transform = view.get<ComTransform>(entity);
			auto& anime = view.get<ComAnimation>(entity);
			auto& characterAnimation = view.get<ComCharacterAnimation>(entity);

			// for stop movement
			if (sharedKeyboard.isKeyUp(SharedKeyboard::UP)) {
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::BACK_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::DOWN)) {
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::FRONT_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::LEFT)) {
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::LEFT_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::RIGHT)) {
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::RIGHT_STOP;
			}
			
			// for movement
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::UP)) {
				velocity.y += -1.f;	
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::BACK;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::DOWN)) {
				velocity.y += 1.f;
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::FRONT;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::LEFT)) {
				velocity.x += -1.f;
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::LEFT;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::RIGHT)) {
				velocity.x += 1.f;
				characterAnimation.nextAnimeDir = SharedCharacterAnimations::RIGHT;
				doMovement(transform, velocity, dt);
			}



			
		}
	}

}