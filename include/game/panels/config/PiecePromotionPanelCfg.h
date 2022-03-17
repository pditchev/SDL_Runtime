#ifndef INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONPANELCFG_H_
#define INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONPANELCFG_H_
//C system headers

//C++ system headers
#include <cstdint>


//Other libraries headers

//Own components headers

//Forward declaration
//struct GameProxy;

struct PiecePromotionPanelCfg {
	//mutable GameProxy *gameProxy = nullptr;
	int32_t whitePiecesRsrcId = 0;
	int32_t blackPiecesRsrcId = 0;
	int32_t buttonBgrRsrcId = 0;
	int32_t gameBoardWidth = 0;
	int32_t gameBoatdHeight = 0;
	int32_t buttonBgrWidth = 0;
	int32_t buttonBgrHeight = 0;
	int32_t buttonWidth = 0;
	int32_t buttonHeight = 0;
};



#endif /* INCLUDE_GAME_PANELS_CONFIG_PIECEPROMOTIONPANELCFG_H_ */
