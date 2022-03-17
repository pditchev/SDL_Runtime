#ifndef GAME_CONFIG_GAMECFG_H_
#define GAME_CONFIG_GAMECFG_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/panels/config/PiecePromotionPanelCfg.h"

//Forward declaration

enum GameImages { UP, DOWN, LEFT, RIGHT, ALL_KEYS, LAYER_2, COUNT };

struct GameCfg{
	PiecePromotionPanelCfg piecePromotionPanelCfg;

	int32_t chessBoardRsrcId;
	int32_t whitePiecesRsrcId;
	int32_t blackPiecesRsrcId;
	int32_t targetRsrcId;

	int32_t moveTilesRsrcId;

	int32_t unfinishedPieceTextId;

	int32_t blinkTargetTimerId;
	int32_t timerCapTimerId;
	int32_t consoleFontId;
};


#endif /* GAME_CONFIG_GAMECFG_H_ */
