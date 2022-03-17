#ifndef ENGINE_CONFIG_ENGINECONFIG_H_
#define ENGINE_CONFIG_ENGINECONFIG_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "manager_utils/config/ManagerHandlerCfg.h"
#include "game/config/GameCfg.h"

//Forward declaration

struct EngineConfig{
	ManagerHandlerCfg managerHandlerCfg;
	GameCfg gameCfg;

	int32_t debugConsoleFontId;

};

#endif /* ENGINE_CONFIG_ENGINECONFIG_H_ */
