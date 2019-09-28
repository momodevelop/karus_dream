#include <array>
#include <random>

#include "shared_spawner.h"
#include "../components/com_transform.h"
#include "../components/com_renderable.h"
#include "../components/com_box_collider.h"
#include "../components/com_animation.h"
#include "../components/com_collectible.h"
#include "../components/com_enemy.h"

#include <constants.h>



namespace app::game::shared {
	using namespace components;
	using namespace ryoji::math;
	using namespace shared;
	const static Vec2f enemySizes[SharedSpawner::MAX]{
		{ gEnemySize, gEnemySize }, // GHOST
		{ gEnemySize * 2, gEnemySize * 2 }, // SKELETON
		{ gEnemySize, gEnemySize }, // FROG
		{ gEnemySize, gEnemySize }, // BAT
	};

	struct EnemyTypeInfo {
		TextureHandler texture;
		SharedAnimationIndices::Indices animationIndex;
		uint8_t hp;
		std::array<Vec2f, 2> spawnLocations;
	};
	const static EnemyTypeInfo enemyInfos[SharedSpawner::MAX] = {
		{ 
			TextureHandler::GHOST_SPRITESHEET, 
			SharedAnimationIndices::ENEMY_GHOST, 
			3, 
			{
				Vec2f{-enemySizes[SharedSpawner::GHOST].x, 100.f},
				Vec2f{enemySizes[SharedSpawner::GHOST].x, 100.f}
			}
		}, // GHOST

		{ 
			TextureHandler::SKELETON_SPRITESHEET, 
			SharedAnimationIndices::ENEMY_SKELETON, 
			3, 
			{
				Vec2f{-enemySizes[SharedSpawner::SKELETON].x, gDisplayHalfHeight - enemySizes[SharedSpawner::SKELETON].y},
				Vec2f{enemySizes[SharedSpawner::SKELETON].x, gDisplayHalfHeight - enemySizes[SharedSpawner::SKELETON].y}
			}
		}, // SKELETON
		{ 
			TextureHandler::FROG_SPRITESHEET, 
			SharedAnimationIndices::ENEMY_FROG, 
			3,
			{
				Vec2f{-enemySizes[SharedSpawner::FROG].x, gDisplayHalfHeight - enemySizes[SharedSpawner::FROG].y},
				Vec2f{enemySizes[SharedSpawner::FROG].x, gDisplayHalfHeight - enemySizes[SharedSpawner::FROG].y}
			}
		}, // FROG
		{
			TextureHandler::BAT_SPRITESHEET,
			SharedAnimationIndices::ENEMY_BAT,
			3,
			{
				Vec2f{-enemySizes[SharedSpawner::BAT].x, 100.f},
				Vec2f{enemySizes[SharedSpawner::BAT].x, 100.f}
			}
		},// BAT
	};


	SharedSpawner::SharedSpawner(entt::registry& ecs, SharedAnimationIndices& animationIndices) :
		coinTimer(0.f), coinDuration(5.f),
		enemyTimer(0.f), enemyDuration(5.f),
		ecs(ecs), 
		animationIndices(animationIndices),
		randomGenerator(randomDevice()),
		randomCoinX(gTileSize, gDisplayWidth - gHalfTileSize),
		randomCoinY(gTileSize, gDisplayHalfHeight - gHalfTileSize),
		randomEnemyType(GHOST, BAT),
		randomCoinFlip(false, true)
	{
	}
	SharedSpawner::~SharedSpawner()
	{
	}
	void SharedSpawner::update(float dt)
	{
		// coin spawn logic here
		coinTimer += dt;
		if (coinTimer > coinDuration) {
			int x = randomCoinX(randomGenerator);
			int y = randomCoinY(randomGenerator);
			spawnCoin(Vec2f{ float(x), float(y) });
			coinTimer = 0.f;
		}

		// enemy spawner
		enemyTimer += dt;
		if (enemyTimer > enemyDuration) {
			EnemyType type = (EnemyType)randomEnemyType(randomGenerator);
			spawnEnemy(randomCoinFlip(randomGenerator), type);
			enemyTimer = 0.f;
		}


	}

	void SharedSpawner::spawnEnemy(bool facingRight, EnemyType type)
	{
		auto entity = ecs.create();
		auto& transform = ecs.assign<ComTransform>(entity, 
			enemyInfos[type].spawnLocations[facingRight], 
			enemySizes[type],
			0.f, 
			facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL
		);

		auto& enemy = ecs.assign<ComEnemy>(entity,
			facingRight ? ComEnemy::STATE_MOVING_RIGHT : ComEnemy::STATE_MOVING_LEFT,
			enemyInfos[type].hp
		);
		auto& boxCollider = ecs.assign<ComBoxCollider>(entity,
			ryoji::aabb::AABB2f{ 0.f, 0.f, enemySizes[type].x, enemySizes[type].y }
		);
		
		auto& renderable = ecs.assign<ComRenderable>(entity);

		renderable.textureHandler = enemyInfos[type].texture;
		auto& animation = ecs.assign<ComAnimation>(entity);
		auto& indices = animationIndices[enemyInfos[type].animationIndex];
		animation.indices.assign(indices.cbegin(), indices.cend());
		animation.speed = character::gAnimeSpeed;
	}

	void SharedSpawner::spawnCoin(Vec2f pos)
	{
		auto entity = ecs.create();
		ecs.assign<ComTransform>(entity, pos, Vec2f{ float(gHalfTileSize), float(gHalfTileSize) });

		auto& renderable = ecs.assign<ComRenderable>(entity);
		renderable.textureHandler = TextureHandler::COIN_SPRITESHEET;

		ecs.assign<ComCollectible>(entity);
		ecs.assign<ComBoxCollider>(entity, ryoji::aabb::AABB2f{ 0.f, 0.f, float(gHalfTileSize), float(gHalfTileSize) });

		auto& animation = ecs.assign<ComAnimation>(entity);
		auto& indices = animationIndices[SharedAnimationIndices::COIN];
		animation.indices.assign(indices.cbegin(), indices.cend());
		animation.speed = character::gAnimeSpeed;
	}
}

