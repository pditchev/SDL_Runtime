#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "sdl_utils/config/MonitorWindowCfg.h"

//Own includes

//Forward declaration

struct DrawMgrCfg{
	MonitorWindowCfg windowCfg;

	int64_t maxFrameRate;
};


#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_CONFIG_DRAWMGRCFG_H_ */
