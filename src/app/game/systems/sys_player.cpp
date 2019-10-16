
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
#include "../shared/shared_animation_indices.h"
#include "../shared/shared_game_state.h"

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

	void SysPlayer::updateTriggerPositions(entt::registry & ecs, entt::entity player)
	{
		auto* playerTransform = ecs.try_get<ComTransform>(player);
		auto* playerBox = ecs.try_get<ComBoxCollider>(player);
		auto* playerCom = ecs.try_get<ComPlayer>(player);
		auto* playerRigidBody = ecs.try_get<ComRigidBody>(player);
		

		if (playerTransform && playerBox && playerCom && playerRigidBody) {
			auto* jumpTrigger1 = ecs.try_get<ComTransform>(playerCom->jumpTriggers[0]);
			if (jumpTrigger1) {
				jumpTrigger1->position = playerTransform->position + Vec2f{ 5.f, playerBox->box.max[1] };
			}
			auto jumpTrigger2 = ecs.try_get<ComTransform>(playerCom->jumpTriggers[1]);
			if (jumpTrigger2) {
				jumpTrigger2->position = playerTransform->position + Vec2f{ playerBox->box.max[0] - gJumpTriggerSize - 5.f, playerBox->box.max[1] };
			}

			auto weaponTrigger = ecs.try_get<ComTransform>(playerCom->weaponTrigger);
			if (weaponTrigger) {
				if (playerCom->state == ComPlayer::STATE_MOVING_LEFT) // going left
				{
					// adjust trigger position
					auto weaponTransform = ecs.try_get<ComTransform>(playerCom->weaponTrigger);
					auto weaponBox = ecs.try_get<ComBoxCollider>(playerCom->weaponTrigger);
					if (weaponTransform && weaponBox) {
						float weaponWidth = weaponBox->box.max[0] - weaponBox->box.min[0];
						float weaponHeight = weaponBox->box.max[1] - weaponBox->box.min[1];
						float playerWidth = playerBox->box.max[0] - playerBox->box.min[0];
						float playerHeight = playerBox->box.max[1] - playerBox->box.min[1];
						weaponTransform->position.x = playerTransform->position.x - weaponWidth + playerWidth * 0.5f;
						weaponTransform->position.y = playerTransform->position.y + playerHeight * 0.5f - weaponHeight * 0.5f + 10.f;
						weaponTransform->flipState = SDL_FLIP_HORIZONTAL;
					}
				}
				else if (playerCom->state == ComPlayer::STATE_MOVING_RIGHT) {
					// adjust trigger position
					auto weaponTransform = ecs.try_get<ComTransform>(playerCom->weaponTrigger);
					auto weaponBox = ecs.try_get<ComBoxCollider>(playerCom->weaponTrigger);
					if (weaponTransform && weaponBox) {
						float weaponHeight = weaponBox->box.max[1] - weaponBox->box.min[1];
						float playerWidth = playerBox->box.max[0] - playerBox->box.min[0];
						float playerHeight = playerBox->box.max[1] - playerBox->box.min[1];

						weaponTransform->position.x = playerTransform->position.x + playerWidth * 0.5f;
						weaponTransform->position.y = playerTransform->position.y + playerHeight * 0.5f - weaponHeight * 0.5f + 10.f;
						weaponTransform->flipState = SDL_FLIP_NONE;
					}
				}

				

			}
		}
	}

	void SysPlayer::processInput(entt::registry& ecs, SharedKeyboard& sharedKeyboard, entt::entity player, shared::SharedGameState& sharedGameState) {
		using namespace character;
		
		using SharedAnime = SharedAnimationIndices; // so that I don't have to type lol

		auto* rigidbody = ecs.try_get<ComRigidBody>(player);
		auto* characterAnimation = ecs.try_get<ComCharacterAnimation>(player);
		auto* playerCom = ecs.try_get<ComPlayer>(player);

		if (rigidbody && characterAnimation) {
			Vec2f direction { 0.f, 0.f };

			if (playerCom->state != ComPlayer::STATE_DIE) {
				// movement
				if (sharedKeyboard.isKeyDown(SharedKeyboard::LEFT)) {
					rigidbody->velocity.x = -character::gMoveSpeed;
					characterAnimation->nextAnimeDir = SharedAnime::CHARACTER_NORM_LEFT;
					playerCom->state = ComPlayer::STATE_MOVING_LEFT;
					sharedGameState.state = SharedGameState::GAME_UPDATE;
				}
				else if (sharedKeyboard.isKeyDown(SharedKeyboard::RIGHT)) {
					rigidbody->velocity.x = character::gMoveSpeed;
					characterAnimation->nextAnimeDir = SharedAnime::CHARACTER_NORM_RIGHT;
					playerCom->state = ComPlayer::STATE_MOVING_RIGHT;
					sharedGameState.state = SharedGameState::GAME_UPDATE;
				}

				// jump
				if (sharedKeyboard.isKeyDown(SharedKeyboard::Z) && playerCom->jumpTimer >= playerCom->jumpCooldown) {
					rigidbody->velocity.y = -character::gJump;
					playerCom->jumpTimer = 0.f;
				}
			}
		}

	}

}