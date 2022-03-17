// Corresponding Header
#include "manager_utils/managers/DrawMgr.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes
#include "manager_utils/config/DrawMgrCfg.h"
#include "manager_utils/managers/RsrcMgr.h"

DrawMgr *gDrawMgr = nullptr;

int32_t DrawMgr::init(const DrawMgrCfg& cfg){
	if(EXIT_SUCCESS != _window.init(cfg.windowCfg)){
		std::cerr << "window.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _renderer.init(_window.getWindow())){
		std::cerr << "window.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	_maxFrames = cfg.maxFrameRate;

	return EXIT_SUCCESS;
}

void DrawMgr::deinit() {
	_renderer.deinit();
	_window.deinit();
}

void DrawMgr::process() {

}

void DrawMgr::clearScreen(){
	_renderer.clearScreen();
}

void DrawMgr::finishFrame(){
	_renderer.finishFrame();
}

void DrawMgr::addDrawCmd(const DrawParams &drawParams) const {
	SDL_Texture* texture = getTextureInternal(drawParams);
	_renderer.renderTexture(texture, drawParams);
}

int64_t DrawMgr::getMaxFrameRate() const {
	return _maxFrames;
}


SDL_Texture* DrawMgr::getTextureInternal(const DrawParams &drawParams) const {
	if(WidgetType::IMAGE == drawParams.widgetType){
		return gRsrcMgr->getImageTexture(drawParams.rsrcId);
	} else if(WidgetType::TEXT == drawParams.widgetType){
		return gRsrcMgr->getTextTexture(drawParams.textId);
	} else {
		std::cerr << "Error, received unsupported WidgetType: "
				  << static_cast<int32_t>(drawParams.widgetType)
				  << " for rsrcId: " << drawParams.rsrcId << std::endl;
	}
	return nullptr;
}

void DrawMgr::setWidgetBlendMode(const DrawParams &drawParams, BlendMode blendMode){
	SDL_Texture* texture = getTextureInternal(drawParams);
	_renderer.setWidgetBlendMode(texture, blendMode);
}

void DrawMgr::setWidgetOpacity(const DrawParams &drawParams, int32_t opacity){
	if(drawParams.widgetType == WidgetType::IMAGE){
		return;
	}

	SDL_Texture* texture = getTextureInternal(drawParams);
	_renderer.setWidgetOpacity(texture, opacity);
}








