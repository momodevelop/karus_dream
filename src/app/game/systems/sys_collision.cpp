#include <ryoji/collision.h>
#include <SDL.h>


#include "../components/com_player.h"
#include "../components/com_obstacle.h"
#include "../components/com_box_collider.h"
#include "../components/com_transform.h"
#include "../components/com_collectible.h"
#include "../components/com_rigidbody.h"

#include "../shared/shared_score.h"

#include "sys_collision.h"

namespace app::game::systems {
	using namespace components;
	using namespace ryoji;



	void SysCollision::syncBoxColliderToTransform(components::ComBoxCollider& collider, const components::ComTransform& transform)
	{
		aabb::translate(collider.box, transform.position.x, 0);
		aabb::translate(collider.box, transform.position.y, 1);
	}

	void SysCollision::resolvePlayerJumpTriggerCollision(entt::registry & ecs, entt::entity playerEntity)
	{
		auto obstacles = ecs.view<ComTransform, ComBoxCollider, ComPlayerObstacle>();

		auto* playerCom = ecs.try_get<ComPlayer>(playerEntity);
		if (!playerCom)
			return;

		// Get the jump triggers
		std::array<ComBoxCollider, 2> jumpTriggerBoxColliders;
		for (size_t i = 0; i < 2; ++i) {
			auto* collider = ecs.try_get<ComBoxCollider>(playerCom->jumpTriggers[i]);
			auto* transform = ecs.try_get<ComTransform>(playerCom->jumpTriggers[i]);
			if (!collider || !transform) {
				return;
			}

			jumpTriggerBoxColliders[i] = *collider;

			syncBoxColliderToTransform(jumpTriggerBoxColliders[i], *transform);
		}


		for (auto obstacle : obstacles) {
			auto& obstacleTransform = obstacles.get<ComTransform>(obstacle);
			auto obstacleBox = obstacles.get<ComBoxCollider>(obstacle); //copy

			// Sync player and obstacle's rect to transform
			syncBoxColliderToTransform(obstacleBox, obstacleTransform);

			// check collision
			for (auto& collider : jumpTriggerBoxColliders) {
				if (aabb::isAABBColliding(obstacleBox.box, collider.box)) {
					playerCom->jumpTimer = playerCom->jumpCooldown;
					return; // return... don't have to check for other obstacles. 
				}
			}


		}
		
		
	}

	void SysCollision::resolvePlayerCollideCollectible(entt::registry & ecs, entt::entity playerEntity, shared::SharedScore& sharedScore)
	{
		auto collectibles = ecs.view<ComTransform, ComBoxCollider, ComCollectible>();

		auto* playerTransform = ecs.try_get<ComTransform>(playerEntity);
		auto* playerBox = ecs.try_get<ComBoxCollider>(playerEntity);
		auto* playerRb = ecs.try_get<ComRigidBody>(playerEntity);

		if (playerTransform && playerBox && playerRb) {
			auto playerBoxCopy = *playerBox;

			syncBoxColliderToTransform(playerBoxCopy, *playerTransform);

			for (auto collectible : collectibles) {

				auto& collectibleTransform = collectibles.get<ComTransform>(collectible);
				auto collectibleBox = collectibles.get<ComBoxCollider>(collectible); //copy

				// Sync player and collectible's rect to transform
				aabb::translate(collectibleBox.box, collectibleTransform.position.x, 0);
				aabb::translate(collectibleBox.box, collectibleTransform.position.y, 1);
				

				if (aabb::isAABBColliding(playerBoxCopy.box, collectibleBox.box)) {
					ecs.destroy(collectible);
					sharedScore.addScore(1);
				}


			}
		}
	}

	void SysCollision::resolvePlayerCollideObstacle(entt::registry & ecs, entt::entity playerEntity)
	{
		auto obstacles = ecs.view<ComTransform, ComBoxCollider, ComPlayerObstacle>();

		auto* playerTransform = ecs.try_get<ComTransform>(playerEntity);
		auto* playerBox = ecs.try_get<ComBoxCollider>(playerEntity);
		auto* playerRb = ecs.try_get<ComRigidBody>(playerEntity);

		if(playerTransform && playerBox && playerRb) {
			auto playerBoxCopy = *playerBox;

			syncBoxColliderToTransform(playerBoxCopy, *playerTransform);

			for (auto obstacle : obstacles) {
			
				auto& obstacleTransform = obstacles.get<ComTransform>(obstacle);
				auto obstacleBox = obstacles.get<ComBoxCollider>(obstacle); //copy

				// Sync player and obstacle's rect to transform
				syncBoxColliderToTransform(obstacleBox, obstacleTransform);

				auto [pushout, index] = aabb::getCollidingAABBSmallestOverlap(playerBoxCopy.box, obstacleBox.box);
				if (index != 2) {
					playerRb->velocity.arr[index] = 0.f;
					playerTransform->position.arr[index] += pushout;
				}
			}

		}
	}
}