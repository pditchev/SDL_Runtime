// Corresponding Header
#include "manager_utils/managers/RsrcMgr.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes
#include "manager_utils/config/RsrcMgrCfg.h"

RsrcMgr *gRsrcMgr = nullptr;

int32_t RsrcMgr::init(const RsrcMgrCfg& cfg){
	if(EXIT_SUCCESS != ImageContainer::init(cfg.imageContainerCfg)){
		std::cerr << "_imgContainer.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != TextContainer::init(cfg.textContainerCfg)){
		std::cerr << "_textContainer.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void RsrcMgr::deinit() {
	TextContainer::deinit();
	ImageContainer::deinit();
}

void RsrcMgr::process() {

}
