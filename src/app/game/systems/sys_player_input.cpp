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
	using namespace shared;

	void doMovement(ComTransform& transform, Vec2f& velocity, float dt) {
		auto normVelocity = normalize(velocity);
		if (normVelocity.has_value()) {
			transform.position += normVelocity.value() * SPEED * dt;
		}
	}

	void SysPlayerInput::update(entt::registry& registry, SharedKeyboard& sharedKeyboard, float dt) {
		using namespace character;
		
		using SharedAnime = SharedCharacterAnimations; // so that I don't have to type lol

		auto view = registry.view<ComTransform, ComPlayerInput, ComCharacterAnimation>();
		for (auto entity : view) {
			Vec2f velocity { 0.f, 0.f };

			auto& transform = view.get<ComTransform>(entity);
			auto& characterAnimation = view.get<ComCharacterAnimation>(entity);
			
			// for movement
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::UP)) 
				velocity.y += -1.f;	
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::DOWN)) 
				velocity.y += 1.f;
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::LEFT))
				velocity.x += -1.f;
			if (sharedKeyboard.isKeyHeld(SharedKeyboard::RIGHT)) 
				velocity.x += 1.f;

			// animation
			if (velocity.x < 0.f)
				characterAnimation.nextAnimeDir = SharedAnime::NORM_LEFT;
			else if (velocity.x > 0.f)
				characterAnimation.nextAnimeDir = SharedAnime::NORM_RIGHT;
			else if (velocity.y < 0.f)
				characterAnimation.nextAnimeDir = SharedAnime::NORM_UP;
			else if (velocity.y > 0.f)
				characterAnimation.nextAnimeDir = SharedAnime::NORM_DOWN;
			else if (velocity.x == 0.f && velocity.y == 0.f) {
				// we can compare 0.f directly because we didn't do any calculations
				switch (characterAnimation.currentAnimeDir) {
				case SharedAnime::NORM_DOWN:
					characterAnimation.nextAnimeDir = SharedAnime::STOP_DOWN;
					break;
				case SharedAnime::NORM_LEFT:
					characterAnimation.nextAnimeDir = SharedAnime::STOP_LEFT;
					break;
				case SharedAnime::NORM_RIGHT:
					characterAnimation.nextAnimeDir = SharedAnime::STOP_RIGHT;
					break;
				case SharedAnime::NORM_UP:
					characterAnimation.nextAnimeDir = SharedAnime::STOP_UP;
					break;
				}
			}
			
			doMovement(transform, velocity, dt);
			
		}
	}

}