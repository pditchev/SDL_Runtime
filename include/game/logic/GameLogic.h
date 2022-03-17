#ifndef INCLUDE_GAME_LOGIC_GAMELOGIC_H_
#define INCLUDE_GAME_LOGIC_GAMELOGIC_H_
//C system headers

//C++ system headers
#include <cstdint>
#include <functional>

//Other libraries headers

//Own components headers
#include "game/defines/ChessDefines.h"

//Forward declaration

class GameLogic {
public:
	GameLogic();
	void finishTurn();
	Defines::PlayerId getActivePlayerId() const; //my
	void setCheck();
	void removeCheck();
	bool isCheckAnnonced() const;
//	void startTimerCap();


	std::function<void()> restartTimer;
	std::function<void(const Defines::PlayerId&)> announceCheck;

private:
	Defines::PlayerId _activePlayerId;
	bool _check = false;

};

#endif /* INCLUDE_GAME_LOGIC_GAMELOGIC_H_ */
