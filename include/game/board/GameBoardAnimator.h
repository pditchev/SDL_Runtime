#ifndef INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_
#define INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "utils/drawing/DrawParams.h"

//Forward declaration
struct GameProxy;
struct Image;

class GameBoardAnimator {
public:
	int32_t init(GameProxy *gameProxy, Image *boardImg);
	void startAnim(int32_t playerId);
private:
	GameProxy *_gameProxy = nullptr;
	Image *_boardImg = nullptr;
	int32_t _currRotation { 0 };
	WidgetFlip _targetFlipType = WidgetFlip::NONE;
};

#endif /* INCLUDE_GAME_BOARD_GAMEBOARDANIMATOR_H_ */
