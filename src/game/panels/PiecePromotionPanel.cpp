// Corresponding Header
#include "game/panels/PiecePromotionPanel.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "sdl_utils/InputEvent.h"

int32_t PiecePromotionPanel::init(const PiecePromotionPanelCfg &cfg){

	PiecePromotionButtonCfg btnCfg;

	btnCfg.onBtnClicked = std::bind(&PiecePromotionPanel::onButtonClicked, this, std::placeholders::_1);
//	btnCfg.onBtnClicked = [this](PieceType pieceType){ onButtonClicked(pieceType); };

	btnCfg.buttonBgrRsrcId = cfg.buttonBgrRsrcId;
	btnCfg.buttonWhitePieceRsrcId = cfg.whitePiecesRsrcId;
	btnCfg.buttonBlackPieceRsrcId = cfg.blackPiecesRsrcId;
	btnCfg.bgrWidth = cfg.buttonBgrWidth;
	btnCfg.bgrHeight = cfg.buttonBgrHeight;
	btnCfg.width = cfg.buttonWidth;
	btnCfg.height = cfg.buttonHeight;


	constexpr std::array<PieceType, BUTTONS_COUNT> pieceTypes {
		PieceType::QUEEN, PieceType::ROOK, PieceType::BISHOP, PieceType::KNIGHT
	};

	constexpr auto btnOffset = 50;
	const auto startX = (cfg.gameBoardWidth - (BUTTONS_COUNT * (cfg.buttonWidth + btnOffset))) / 2;
	btnCfg.bgrPos._y = (cfg.gameBoatdHeight - cfg.buttonHeight ) / 2;

	auto i = 0;
	for(const auto& piece : pieceTypes){
		btnCfg.pieceType = piece;
		btnCfg.bgrPos._x = startX + i * (cfg.buttonWidth + btnOffset);
		if(EXIT_SUCCESS != _promotionBtns[i++].init(btnCfg)){
			std::cerr << "Error, promotion button with idx "
					  << static_cast<int32_t>(piece) << " was not created" << std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

void PiecePromotionPanel::onButtonClicked(PieceType pieceType){
	_isActive = false;
	promotePiece(pieceType);
}


void PiecePromotionPanel::handleEvent(const InputEvent &e){
	for(auto& btn : _promotionBtns){
		if(btn.isInputUnlocked() && btn.containsEvent(e)){
			btn.handleEvent(e);
			break;
		}
	}
}

void PiecePromotionPanel::draw() const{
	if(!_isActive){
		return;
	}

	for(const auto& btn : _promotionBtns){
		btn.draw();
	}
}

void PiecePromotionPanel::activate(int32_t playerId){
	_isActive = true;
	for(auto& btn : _promotionBtns){
		btn.activate(playerId);
	}
}

bool PiecePromotionPanel::isActive() const{
	return _isActive;
}









