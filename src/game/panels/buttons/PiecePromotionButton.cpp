// Corresponding Header
#include "game/panels/buttons/PiecePromotionButton.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "sdl_utils/InputEvent.h"

int32_t PiecePromotionButton::init(const PiecePromotionButtonCfg &cfg){
	_cfg = cfg;
	_bgrImg.create(cfg.buttonBgrRsrcId, cfg.bgrPos);

	return EXIT_SUCCESS;
}

void PiecePromotionButton::draw() const {
	_bgrImg.draw();
	ButtonBase::draw();
}

void PiecePromotionButton::handleEvent(const InputEvent &e)  {
	if(TouchEvent::TOUCH_PRESS == e.type){
		_bgrImg.setFrame(CLICKED);
	} else if(TouchEvent::TOUCH_RELEASE == e.type){
		_bgrImg.setFrame(UNCLICKED);
		_cfg.onBtnClicked(_cfg.pieceType);
	}
}

void PiecePromotionButton::activate(int32_t activePlayerId){
	const auto& rsrcId = activePlayerId == Defines::WHITE_PLAYER_ID ?
					_cfg.buttonWhitePieceRsrcId : _cfg.buttonBlackPieceRsrcId;

	const int32_t X_Y_DELTA = (_bgrImg.getWidth() - _cfg.width) / 2;

	const Point btnPos = Point(_bgrImg.getX() + X_Y_DELTA, _bgrImg.getY() + X_Y_DELTA);

	if(isCreated()){
		ButtonBase::destroy();
	}
	ButtonBase::create(rsrcId, btnPos);

	setFrame(static_cast<int32_t>(_cfg.pieceType));
}











