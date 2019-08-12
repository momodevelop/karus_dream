#ifndef __APP_GAME_I_PLAYER_CONTROLLABLE_H__
#define __APP_GAME_I_PLAYER_CONTROLLABLE_H__


namespace app::game {
	struct iPlayerControllable {
		enum MoveDirection { MOVE_NONE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };
		virtual void startMove(MoveDirection dir) = 0;
		virtual void stopMove(MoveDirection dir) = 0;
	};
}


#endif