#ifndef INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_
#define INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "manager_utils/input/ButtonBase.h"
#include "manager_utils/drawing/Image.h"
#include "game/panels/config/PiecePromotionButtonCfg.h"

//Forward declaration
struct InputEvent;

class PiecePromotionButton : public ButtonBase {
public:
	int32_t init(const PiecePromotionButtonCfg &cfg);
	void draw() const final;
	void handleEvent(const InputEvent &e) final;
	void activate(int32_t activePlayerId);
private:
	Image _bgrImg;
	PiecePromotionButtonCfg _cfg;
};

#endif /* INCLUDE_GAME_PANELS_BUTTONS_PIECEPROMOTIONBUTTON_H_ */
