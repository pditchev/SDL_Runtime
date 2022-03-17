// Corresponding Header
#include "game/logic/GameLogic.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes

GameLogic::GameLogic() : _activePlayerId(Defines::WHITE_PLAYER_ID){}

Defines::PlayerId GameLogic::getActivePlayerId() const{ //my
	return _activePlayerId;
}

void GameLogic::finishTurn(){
	_activePlayerId = (_activePlayerId == Defines::WHITE_PLAYER_ID)	?
			Defines::BLACK_PLAYER_ID : Defines::WHITE_PLAYER_ID;

	restartTimer();
}

void GameLogic::setCheck() {
	_check = true;
	announceCheck(_activePlayerId);
}

void GameLogic::removeCheck(){
	if(_check){
		_check = false;
	}
}

bool GameLogic::isCheckAnnonced() const {
	return _check;
}







