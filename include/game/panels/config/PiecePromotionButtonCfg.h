#ifndef INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONBUTTONCFG_H_
#define INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONBUTTONCFG_H_
//C system headers

//C++ system headers
#include <functional>

//Other libraries headers

//Own components headers
#include "game/defines/ChessDefines.h"

//Forward declaration

struct PiecePromotionButtonCfg {
	std::function<void(PieceType)> onBtnClicked; //capture the method by lambda or using std::bind
	Point bgrPos = Point::UNDEFINED;
	int32_t buttonBgrRsrcId;
	int32_t buttonWhitePieceRsrcId;
	int32_t buttonBlackPieceRsrcId;
	int32_t bgrWidth = 0;
	int32_t bgrHeight = 0;
	int32_t width = 0;
	int32_t height = 0;
	PieceType pieceType = PieceType::UNKNOWN;
};



#endif /* INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONBUTTONCFG_H_ */
