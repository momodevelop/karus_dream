#ifndef __APP_GAME_SYSTEMS_PLAYER_H__
#define __APP_GAME_SYSTEMS_PLAYER_H__


namespace app::game::systems {
	class SysPlayer {
	public:
		static void update(entt::registry& ecs, entt::entity player, float dt);
		static void updateTriggerPositions(entt::registry& ecs, entt::entity player);
		static void processInput(entt::registry& registry, shared::SharedKeyboard& sharedKeyboard, entt::entity player, shared::SharedGameState& sharedGameState);
	};


}

#endif