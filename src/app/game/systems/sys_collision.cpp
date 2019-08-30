#include <ryoji/collision.h>
#include <SDL.h>


#include "../components/com_player.h"
#include "../components/com_obstacle.h"
#include "../components/com_box_collider.h"
#include "../components/com_transform.h"
#include "../components/com_collectible.h"
#include "../components/com_rigidbody.h"

#include "sys_collision.h"

namespace app::game::systems {
	using namespace components;
	using namespace ryoji;



	void SysCollision::resolvePlayerCollideCollectible(entt::registry & ecs)
	{
		auto collectibles = ecs.view<ComTransform, ComBoxCollider, ComCollectible>();
		auto players = ecs.view<ComTransform, ComBoxCollider, ComRigidBody, ComPlayer>();

		for (auto collectible : collectibles) {
			for (auto player : players) {
				auto& collectibleTransform = collectibles.get<ComTransform>(collectible);
				auto collectibleBox = collectibles.get<ComBoxCollider>(collectible); //copy

				auto& playerTransform = players.get<ComTransform>(player);
				auto playerBox = players.get<ComBoxCollider>(player); //copy
				auto& playerRb = players.get<ComRigidBody>(player);

				// Sync player and collectible's rect to transform
				aabb::translate(collectibleBox.box, collectibleTransform.position.x, 0);
				aabb::translate(collectibleBox.box, collectibleTransform.position.y, 1);
				aabb::translate(playerBox.box, playerTransform.position.x, 0);
				aabb::translate(playerBox.box, playerTransform.position.y, 1);

				if (aabb::isAABBColliding(playerBox.box, collectibleBox.box)) {
					ecs.destroy(collectible);
				}
			}

		}
	}

	void SysCollision::resolvePlayerCollideObstacle(entt::registry & ecs)
	{
		auto obstacles = ecs.view<ComTransform, ComBoxCollider, ComObstacle>();
		auto players = ecs.view<ComTransform, ComBoxCollider, ComRigidBody, ComPlayer>();

		for (auto obstacle : obstacles) {
			for (auto player : players) {
				auto& obstacleTransform = obstacles.get<ComTransform>(obstacle);
				auto obstacleBox = obstacles.get<ComBoxCollider>(obstacle); //copy
				
				auto& playerTransform = players.get<ComTransform>(player);
				auto playerBox = players.get<ComBoxCollider>(player); //copy
				auto& playerRb = players.get<ComRigidBody>(player);

				// Sync player and obstacle's rect to transform
				aabb::translate(obstacleBox.box, obstacleTransform.position.x, 0);
				aabb::translate(obstacleBox.box, obstacleTransform.position.y, 1);
				aabb::translate(playerBox.box, playerTransform.position.x, 0);
				aabb::translate(playerBox.box, playerTransform.position.y, 1);

				auto [pushout, index] = aabb::getCollidingAABBSmallestOverlap(playerBox.box, obstacleBox.box);
				if (index != 2) {
					playerRb.velocity.arr[index] = 0.f;
					playerTransform.position.arr[index] += pushout;
				}
			}

		}
	}
}