#ifndef INCLUDE_GAME_PANELS_PIECEPROMOTIONPANEL_H_
#define INCLUDE_GAME_PANELS_PIECEPROMOTIONPANEL_H_
//C system headers

//C++ system headers
#include <array>

//Other libraries headers

//Own components headers
#include "game/panels/config/PiecePromotionPanelCfg.h"
#include "game/panels/buttons/PiecePromotionButton.h"

//Forward declaration
struct InputEvent;

class PiecePromotionPanel {
public:
	int32_t init(const PiecePromotionPanelCfg &cfg);
	void handleEvent(const InputEvent &e);
	void draw() const;
	void activate(int32_t playerId);
	bool isActive() const;

	//my
	std::function<void(PieceType)> promotePiece;
private:
	void onButtonClicked(PieceType pieceType);

	enum InternalDefines {
		BUTTONS_COUNT = 4
	};

	std::array<PiecePromotionButton, BUTTONS_COUNT> _promotionBtns;

	bool _isActive = false;
};

#endif /* INCLUDE_GAME_PANELS_PIECEPROMOTIONPANEL_H_ */
