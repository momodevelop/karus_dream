#ifndef __APP_GAME_SYSTEMS_INPUT_H__
#define __APP_GAME_SYSTEMS_INPUT_H__


namespace app::game::systems {
	class SysInput {
	public:
		static void update(entt::registry& registry, shared::SharedKeyboard& sharedKeyboard);
	};


}

#endif