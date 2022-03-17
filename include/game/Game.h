#ifndef GAME_GAME_H_
#define GAME_GAME_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "config/GameCfg.h"
#include "manager_utils/drawing/Image.h"
#include "game/board/GameBoard.h"
#include "game/pieces/types/ChessPiece.h"
#include "game/pieces/PieceHandler.h"
#include "game/logic/GameLogic.h"
#include "game/panels/ManagementConsole.h"
//#include "game/logic/InputInverter.h"
//#include "game/proxies/GameProxy.h"
#include "game/panels/PiecePromotionPanel.h"
//#include "game/board/GameBoardAnimator.h"

//Forward declaration
struct InputEvent;

//class Game : public GameProxy {
class Game {
public:
	int32_t init(const GameCfg& cfg);
	void deinit();
	void draw() const;
	void handleEvent(InputEvent& e);

	void checkMate();

private:

//	void onBoardAnimFinished() final;
//
//	void setWidgetFlip(WidgetFlip flipType) final;


	GameBoard _gameBoard;
	PieceHandler _pieceHandler;
	GameLogic _gameLogic;
	PiecePromotionPanel _piecePromotionPanel;
	ManagementConsole _console;

//	GameBoardAnimator _gameBoardAnimator;
//	InputInverter _inputInverter;
};

#endif /* GAME_GAME_H_ */
