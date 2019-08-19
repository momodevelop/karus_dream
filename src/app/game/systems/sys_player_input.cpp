#include <constants.h>
#include <ryoji/vector.h>

#include "../components/com_transform.h"
#include "../components/com_player_input.h"
#include "../components/com_animation.h"
#include "../components/com_character_animation.h"

#include "sys_player_input.h"

#define SPEED 500.f

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

		auto view = registry.view<ComTransform, ComPlayerInput, ComAnimation, ComCharacterAnimation>();
		for (auto entity : view) {
			Vec2f velocity { 0.f, 0.f };
			

			auto& transform = view.get<ComTransform>(entity);
			auto& anime = view.get<ComAnimation>(entity);
			auto& characterAnimation = view.get<ComCharacterAnimation>(entity);
					
			// for movement
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::UP)) {
				velocity.y += -1.f;	
				characterAnimation.nextAnimeDir = animation::BACK;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::DOWN)) {
				velocity.y += 1.f;
				characterAnimation.nextAnimeDir = animation::FRONT;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::LEFT)) {
				velocity.x += -1.f;
				characterAnimation.nextAnimeDir = animation::LEFT;
				doMovement(transform, velocity, dt);
			}

			if (sharedKeyboard.isKeyHeld(SharedKeyboard::RIGHT)) {
				velocity.x += 1.f;
				characterAnimation.nextAnimeDir = animation::RIGHT;
				doMovement(transform, velocity, dt);
			}

			// for stop movement
			if (sharedKeyboard.isKeyUp(SharedKeyboard::UP)) {
				characterAnimation.nextAnimeDir = animation::BACK_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::DOWN)) {
				characterAnimation.nextAnimeDir = animation::FRONT_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::LEFT)) {
				characterAnimation.nextAnimeDir = animation::LEFT_STOP;
			}
			if (sharedKeyboard.isKeyUp(SharedKeyboard::RIGHT)) {
				characterAnimation.nextAnimeDir = animation::RIGHT_STOP;
			}

			
		}
	}

}