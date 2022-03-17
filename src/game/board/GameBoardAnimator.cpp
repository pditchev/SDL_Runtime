// Corresponding Header
#include "game/board/GameBoardAnimator.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes
#include "manager_utils/drawing/Image.h"
#include "game/proxies/GameProxy.h"
#include "game/defines/ChessDefines.h"


int32_t GameBoardAnimator::init(GameProxy *gameProxy, Image *boardImg){
	if(nullptr == gameProxy){
		std::cerr << "Error, nullptr provided for gameProxy" << std::endl;
		return EXIT_FAILURE;
	}
	_gameProxy = gameProxy;

	if(nullptr == boardImg){
		std::cerr << "Error, nullptr provided for boardImg" << std::endl;
		return EXIT_FAILURE;
	}
	_boardImg = boardImg;

	const Point rotCenter(_boardImg->getWidth() / 2, _boardImg->getHeight() / 2);
	_boardImg->setRotationCenter(rotCenter);

	return EXIT_SUCCESS;
}

void GameBoardAnimator::startAnim(int32_t playerId){
	if(Defines::WHITE_PLAYER_ID == playerId){
		_targetFlipType = WidgetFlip::HORIZONTAL_AND_VERTICAL;
	} else{
		_targetFlipType = WidgetFlip::NONE;
	}

	_boardImg->setFlipType(_targetFlipType);

	_gameProxy->setWidgetFlip(_targetFlipType);

	_gameProxy->onBoardAnimFinished();
}










