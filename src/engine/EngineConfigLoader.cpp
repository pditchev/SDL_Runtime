// Corresponding Header
#include "engine/EngineConfigLoader.h"

// C system includes

// C++ system includes
#include <iostream> //my, to delete !!!

// Third party includes

// Own includes
#include "common/CommonDefines.h"

namespace{
	constexpr auto WINDOW_WIDTH = 1200; // my
	constexpr auto WINDOW_HEIGHT = 900;
	constexpr auto WINDOW_NAME = "I'm gross meister :)";

	constexpr auto CHESS_PIECES_FRAMES = 6;
	constexpr auto CHESS_PIECES_WIDTH_HEIGHT = 96;
	constexpr auto TARGET_IMG_WIDTH_HEIGHT = 98;

	constexpr auto MOVE_TILES_FRAMES = 3;
	constexpr auto MOVE_TILES_IMG_WIDTH_HEIGHT = 98;

	constexpr auto PROMOTION_BTN_FRAMES = 2;
	constexpr auto PROMOTION_BTN_WIDTH_HEIGHT = 104;

	constexpr auto CHESS_BOARD_WIDTH_HEIGHT = 900;

	constexpr auto MAX_FRAMERATE = 60;

	constexpr auto ANGELINE_VINTAGE_40_FONT_SIZE = 40;
	constexpr auto ANGELINE_VINTAGE_80_FONT_SIZE = 80;

}

std::string EngineConfigLoader::getFilePath(const std::string& relativePath){
#ifdef RELEASE_BUILD
	return relativePath;
#else
	return "../" + relativePath;
#endif
}

void EngineConfigLoader::populateMonitorConfig(MonitorWindowCfg& cfg){
	cfg.windowName = WINDOW_NAME;
	cfg.windowWidth = WINDOW_WIDTH; //0x2FFF0000u; //SDL_WINDOWPOS_CENTERED;
	cfg.windowHeight = WINDOW_HEIGHT; //0x2FFF0000u; //SDL_WINDOWPOS_CENTERED;
	cfg.windowFlags = WINDOW_SHOWN;
}

void EngineConfigLoader::populateDrawMgrConfig(DrawMgrCfg& cfg){
	populateMonitorConfig(cfg.windowCfg);
	cfg.maxFrameRate = MAX_FRAMERATE;
}

void EngineConfigLoader::populateGameConfig(GameCfg& cfg){
	cfg.chessBoardRsrcId = TextureId::CHESS_BOARD;
	cfg.whitePiecesRsrcId = TextureId::WHITE_PIECES;
	cfg.blackPiecesRsrcId = TextureId::BLACK_PIECES;
	cfg.targetRsrcId = TextureId::TARGET;
	cfg.blinkTargetTimerId = TimerId::BLINK_TARGET_TIMER_ID;
	cfg.unfinishedPieceTextId = FontId::ANGELINE_VINTAGE_40;
	cfg.moveTilesRsrcId = TextureId::MOVE_TILES;

	cfg.timerCapTimerId = TimerId::TIMER_CAP_TIMER_ID;
	cfg.consoleFontId = FontId::ANGELINE_VINTAGE_40;

	auto& panelCfg = cfg.piecePromotionPanelCfg;

//	panelCfg.gameProxy = nullptr;
	panelCfg.whitePiecesRsrcId = cfg.whitePiecesRsrcId;
	panelCfg.blackPiecesRsrcId = cfg.blackPiecesRsrcId;
	panelCfg.buttonBgrRsrcId = TextureId::PROMOTION_BUTTON;
	panelCfg.gameBoardWidth = CHESS_BOARD_WIDTH_HEIGHT;
	panelCfg.gameBoatdHeight = CHESS_BOARD_WIDTH_HEIGHT;
	panelCfg.buttonBgrWidth = PROMOTION_BTN_WIDTH_HEIGHT;
	panelCfg.buttonBgrHeight = PROMOTION_BTN_WIDTH_HEIGHT;
	panelCfg.buttonWidth = CHESS_PIECES_WIDTH_HEIGHT;
	panelCfg.buttonHeight = CHESS_PIECES_WIDTH_HEIGHT;
}

void EngineConfigLoader::populateImageContainerConfig(ImageContainerCfg& cfg){
	ImageCfg imageCfg;

	imageCfg.location = getFilePath("resources/p/chessBoard.jpg");
	imageCfg.frames.emplace_back(0,0,CHESS_BOARD_WIDTH_HEIGHT, CHESS_BOARD_WIDTH_HEIGHT);
	cfg.imageConfigs.emplace(TextureId::CHESS_BOARD, imageCfg);
	imageCfg.frames.clear();

	constexpr auto buttonsCnt{2};
	constexpr const char* buttonsPaths[buttonsCnt] = {
			"resources/p/whitePieces.png",
			"resources/p/blackPieces.png",
	};

	constexpr int32_t buttonRsrcIds[buttonsCnt] = {
			TextureId::WHITE_PIECES,
			TextureId::BLACK_PIECES
	};

	for(auto i = 0; i < buttonsCnt; ++i){
		imageCfg.location = getFilePath(buttonsPaths[i]);
		for(auto frameId = 0; frameId < CHESS_PIECES_FRAMES; ++frameId){
			imageCfg.frames.emplace_back(
					frameId * CHESS_PIECES_WIDTH_HEIGHT,
					0,
					CHESS_PIECES_WIDTH_HEIGHT,
					CHESS_PIECES_WIDTH_HEIGHT
				);
		}

		cfg.imageConfigs.emplace(buttonRsrcIds[i], imageCfg);

		imageCfg.frames.clear();
	}

	imageCfg.location = getFilePath("resources/p/target.png");
	imageCfg.frames.emplace_back(0,0,TARGET_IMG_WIDTH_HEIGHT, TARGET_IMG_WIDTH_HEIGHT);
	cfg.imageConfigs.emplace(TextureId::TARGET, imageCfg);
	imageCfg.frames.clear();

	imageCfg.location = getFilePath("resources/p/moveTiles.png");
	for(auto frameId = 0; frameId < MOVE_TILES_FRAMES; ++frameId){
		imageCfg.frames.emplace_back(
				frameId * CHESS_PIECES_WIDTH_HEIGHT,
			0,
			MOVE_TILES_IMG_WIDTH_HEIGHT,
			MOVE_TILES_IMG_WIDTH_HEIGHT
		);
	}
	cfg.imageConfigs.emplace(TextureId::MOVE_TILES, imageCfg);
	imageCfg.frames.clear();

	imageCfg.location = getFilePath("resources/p/piecePromoteButtonBgr.png");
	for(auto frameId = 0; frameId < PROMOTION_BTN_FRAMES; ++frameId){
		imageCfg.frames.emplace_back(
				frameId * PROMOTION_BTN_WIDTH_HEIGHT,
			0,
			PROMOTION_BTN_WIDTH_HEIGHT,
			PROMOTION_BTN_WIDTH_HEIGHT
		);
	}
	cfg.imageConfigs.emplace(TextureId::PROMOTION_BUTTON, imageCfg);
	imageCfg.frames.clear();
}

void EngineConfigLoader::populateTextContainerConfig(TextContainerCfg& cfg){
	FontCfg fontCfg;

	fontCfg.location = getFilePath("resources/f/AngelineVintage.ttf");
	fontCfg.fontSize = ANGELINE_VINTAGE_40_FONT_SIZE;
	cfg.fontConfigs.emplace(FontId::ANGELINE_VINTAGE_40, fontCfg);
	fontCfg.fontSize = ANGELINE_VINTAGE_80_FONT_SIZE;
	cfg.fontConfigs.emplace(FontId::ANGELINE_VINTAGE_80, fontCfg);
}

void EngineConfigLoader::populateRsrcMgrConfig(RsrcMgrCfg& cfg){
	populateImageContainerConfig(cfg.imageContainerCfg);
	populateTextContainerConfig(cfg.textContainerCfg);
}

void EngineConfigLoader::populateManagerHandlerCfg(ManagerHandlerCfg& cfg){
	populateDrawMgrConfig(cfg.drawMgrCfg);
	populateRsrcMgrConfig(cfg.rsrcMgrCfg);
}

EngineConfig EngineConfigLoader::loadConfig(){
	EngineConfig cfg;
	populateManagerHandlerCfg(cfg.managerHandlerCfg);
	populateGameConfig(cfg.gameCfg);

	cfg.debugConsoleFontId = FontId::ANGELINE_VINTAGE_40;
	return cfg;
}

