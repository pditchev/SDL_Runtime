// Corresponding Header
#include "game/Game.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes
#include "game/defines/ChessDefines.h"
#include "sdl_utils/InputEvent.h"

#include "utils/drawing/Color.h"
#include "game/pieces/types/Pawn.h"
#include "game/pieces/types/Rook.h"
#include "game/pieces/types/King.h"

int32_t Game::init(const GameCfg& cfg){
	if(EXIT_SUCCESS != _gameBoard.init(cfg.chessBoardRsrcId,
									   cfg.targetRsrcId,
									   cfg.moveTilesRsrcId,
									   cfg.blinkTargetTimerId)){
		std::cerr << "Error! _gameBoard.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _pieceHandler.init(static_cast<GameBoardProxy*>(&_gameBoard),
										  //this,
										  cfg.whitePiecesRsrcId,
										  cfg.blackPiecesRsrcId,
										  cfg.unfinishedPieceTextId)){
		std::cerr << "Error! _pieceHandler.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _piecePromotionPanel.init(cfg.piecePromotionPanelCfg)) {
		std::cerr << "Error! _piecePromotionPanel.init() failed" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _console.init(cfg.consoleFontId, cfg.timerCapTimerId)){
		std::cerr << "_console.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

//	if(EXIT_SUCCESS != _gameBoardAnimator.init(this, &_gameBoard.getBoardImage())) {
//		std::cerr << "Error! _gameBoardAnimator.init() failed" << std::endl;
//		return EXIT_FAILURE;
//	}
//
//	if(EXIT_SUCCESS != _inputInverter.init(_gameBoard.getBoardImage().getWidth(),
//										   _gameBoard.getBoardImage().getHeight())) {
//		std::cerr << "Error! _inputInverter.init() failed" << std::endl;
//		return EXIT_FAILURE;
//	}

	_pieceHandler.getCurrPlayerId = std::bind(&GameLogic::getActivePlayerId, &_gameLogic);
	_pieceHandler.finishTurn = std::bind(&GameLogic::finishTurn, &_gameLogic);
	_pieceHandler.setCheck = std::bind(&GameLogic::setCheck, &_gameLogic);
	_gameLogic.announceCheck = std::bind(&ManagementConsole::onCheck, &_console, std::placeholders::_1);

	_pieceHandler.removeCheck = std::bind(&GameLogic::removeCheck, &_gameLogic);
	_pieceHandler.removeCheck = std::bind(&ManagementConsole::onRemoveCheck, &_console);

	_pieceHandler.checkMate = std::bind(&ManagementConsole::onCheckMate, &_console, std::placeholders::_1);

	_piecePromotionPanel.promotePiece = std::bind(&PieceHandler::promotePiece,
												  &_pieceHandler,
												  std::placeholders::_1);

	for(auto& owner : _pieceHandler._pieces){
		for(auto& piece : owner){

			piece->isCurrPlayerInCheck = std::bind(&GameLogic::isCheckAnnonced, &_gameLogic);

			if(piece->getPieceType() == PieceType::PAWN){
				const auto& pawn = static_cast<Pawn*>(piece.get());
				pawn->selfPromotion = std::bind(&PiecePromotionPanel::activate,
												&_piecePromotionPanel,
												std::placeholders::_1);
			}
		}
	}

	_console.finish = std::bind(&GameLogic::finishTurn, &_gameLogic);
	_console.clearMoveTiles = std::bind(&GameBoard::clearMoveTiles, &_gameBoard);
	_gameLogic.restartTimer = std::bind(&ManagementConsole::startTimerCap, &_console);

	return EXIT_SUCCESS;
}

void Game::deinit(){

}

void Game::checkMate() {
	std::cout << "CHECK and MATE !!!!!!"
			  << " for PlayerId: " << _gameLogic.getActivePlayerId() << std::endl;
}


void Game::draw() const {
	_gameBoard.draw();
	_pieceHandler.draw();
	_piecePromotionPanel.draw();
	_console.draw();
}

void Game::handleEvent(InputEvent& e){

	if(_piecePromotionPanel.isActive()){
		_piecePromotionPanel.handleEvent(e);
		return;
	}

//	_inputInverter.invertEvent(e);

	_pieceHandler.handleEvent(e);
}

//void Game::onBoardAnimFinished() {
//	std::cout << "finishing game turn" << std::endl;
//
//	_gameLogic.finishTurn();
//}

//void Game::setWidgetFlip(WidgetFlip flipType) {
////	_pieceHandler.setWidgetFlip(flipType);
//	_inputInverter.setBoardFlipType(flipType);
//}


