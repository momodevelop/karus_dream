#ifndef __APP_GAME_SYSTEMS_PLAYER_H__
#define __APP_GAME_SYSTEMS_PLAYER_H__


namespace app::game::systems {
	class SysPlayer {
	public:
		static void updateJumpTriggerPosition(entt::registry& ecs);
		static void processInput(entt::registry& registry, shared::SharedKeyboard& sharedKeyboard);
	};


}

#endif