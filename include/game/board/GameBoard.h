#ifndef INCLUDE_GAME_BOARD_GAMEBOARD_H_
#define INCLUDE_GAME_BOARD_GAMEBOARD_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/defines/ChessDefines.h"
#include "manager_utils/drawing/Image.h"
#include "game/proxies/GameBoardProxy.h"
#include "game/board/MoveSelector.h"
#include "manager_utils/time/TimerClient.h"

//Forward declaration

class GameBoard : public GameBoardProxy, public TimerClient {
public:
	int32_t init(int32_t boardRsrcId, int32_t targetRsrcId, int32_t moveTilesRsrcId, int32_t blinkTimerId);
	void draw() const;

	Image& getBoardImage();

	void clearMoveTiles();
private:
	void onPieceGrabbed(const BoardPos& boardPos, const std::vector<TileData> &moveTiles) final;
	void onPieceUngrabbed() final;
	bool isMoveAllowed(const BoardPos &pos) const final;

	void onTimeout(int32_t timerId) final;

	std::vector<TileData> _currMoveTiles;

	Image _boardImg;
	Image _targetImg;

	int32_t _blinkTimerId;

	MoveSelector _moveSelector;
};

#endif /* INCLUDE_GAME_BOARD_GAMEBOARD_H_ */
