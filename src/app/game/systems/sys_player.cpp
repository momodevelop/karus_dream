
#include <entt.h>
#include <SDL.h>


#include <constants.h>
#include <ryoji/vector.h>

#include "../components/com_transform.h"
#include "../components/com_player.h"
#include "../components/com_animation.h"
#include "../components/com_character_animation.h"
#include "../components/com_rigidbody.h"
#include "../components/com_box_collider.h"

#include "../shared/shared_keyboard.h"
#include "../shared/shared_character_animations.h"

#include "sys_player.h"


namespace app::game::systems {
	using namespace components;
	using namespace shared;
	using namespace ryoji::math;
	using namespace shared;


	void SysPlayer::update(entt::registry & ecs, entt::entity player, float dt)
	{
		auto* playerCom = ecs.try_get<ComPlayer>(player);
		if (playerCom) {
			playerCom->jumpTimer += dt;
		}
	}

	void SysPlayer::updateJumpTriggerPosition(entt::registry & ecs, entt::entity player)
	{
		auto* playerTransform = ecs.try_get<ComTransform>(player);
		auto* playerBox = ecs.try_get<ComBoxCollider>(player);
		auto* playerCom = ecs.try_get<ComPlayer>(player);
		

		if (playerTransform && playerBox && playerCom) {
			auto* jumpTrigger1 = ecs.try_get<ComTransform>(playerCom->jumpTriggers[0]);
			if (jumpTrigger1) {
				jumpTrigger1->position = playerTransform->position + Vec2f{ 5.f, playerBox->box.max[1] };
			}
			auto jumpTrigger2 = ecs.try_get<ComTransform>(playerCom->jumpTriggers[1]);
			if (jumpTrigger2) {
				jumpTrigger2->position = playerTransform->position + Vec2f{ playerBox->box.max[0] - gJumpTriggerSize - 5.f, playerBox->box.max[1] };
			}
		}
	}

	void SysPlayer::processInput(entt::registry& ecs, SharedKeyboard& sharedKeyboard, entt::entity player) {
		using namespace character;
		
		using SharedAnime = SharedCharacterAnimations; // so that I don't have to type lol

		auto* rigidbody = ecs.try_get<ComRigidBody>(player);
		auto* characterAnimation = ecs.try_get<ComCharacterAnimation>(player);
		auto* playerCom = ecs.try_get<ComPlayer>(player);

		if (rigidbody && characterAnimation && playerCom) {
			Vec2f direction { 0.f, 0.f };

			// movement
			if (sharedKeyboard.isKeyDown(SharedKeyboard::LEFT)) {
				rigidbody->velocity.x = -character::gMoveSpeed;
				characterAnimation->nextAnimeDir = SharedAnime::NORM_LEFT;
			}
			else if (sharedKeyboard.isKeyDown(SharedKeyboard::RIGHT)) {
				rigidbody->velocity.x = character::gMoveSpeed;
				characterAnimation->nextAnimeDir = SharedAnime::NORM_RIGHT;
			}	

			if (sharedKeyboard.isKeyDown(SharedKeyboard::UP) && playerCom->jumpTimer >= playerCom->jumpCooldown) {
				rigidbody->velocity.y = -character::gJump;
				playerCom->jumpTimer = 0.f;

			}
		}

	}

}