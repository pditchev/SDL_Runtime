// Corresponding Header
#include "game/board/GameBoard.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "game/utils/BoardUtils.h"


int32_t GameBoard::init(int32_t boardRsrcId, int32_t targetRsrcId, int32_t moveTilesRsrcId, int32_t blinkTimerId){
	_boardImg.create(boardRsrcId);
	_targetImg.create(targetRsrcId);
	_targetImg.hide();

	if(EXIT_SUCCESS != _moveSelector.init(moveTilesRsrcId)){
		std::cerr << "Error! _moveSelector.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	_blinkTimerId = blinkTimerId;
	return EXIT_SUCCESS;
}

void GameBoard::draw() const {
	_boardImg.draw();
	_targetImg.draw();
	_moveSelector.draw();
}

void GameBoard::onPieceGrabbed(const BoardPos& boardPos, const std::vector<TileData> &moveTiles){
	_currMoveTiles = moveTiles;

	//
	_moveSelector.markTiles(_currMoveTiles);

	_targetImg.show();
	_targetImg.setPosition(BoardUtils::getAbsPos(boardPos));

	startTimer(500, _blinkTimerId, TimerType::PULSE);
}

void GameBoard::onPieceUngrabbed(){
	_moveSelector.unmarkTiles();
	_currMoveTiles.clear();

	if(isActiveTimerId(_blinkTimerId)){
		stopTimer(_blinkTimerId);
	}

	_targetImg.hide();
}

void GameBoard::onTimeout(int32_t timerId) {
	if(_blinkTimerId == timerId){
		if(_targetImg.isVisible()){
			_targetImg.hide();
		} else {
			_targetImg.show();
		}
	} else{
		std::cerr << "Received unsupported timerId: " << timerId << std::endl;
	}
}

bool GameBoard::isMoveAllowed(const BoardPos &pos) const {
	for(const auto& moveTile : _currMoveTiles){
		if(moveTile.boardPos == pos){
			if(moveTile.tileType == TileType::MOVE ||
			   moveTile.tileType == TileType::TAKE){
				return true;
			}
		}
	}
	return false;
}

Image& GameBoard::getBoardImage() {
	return _boardImg;
}

void GameBoard::clearMoveTiles(){
	onPieceUngrabbed();
}






