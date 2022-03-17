#ifndef ENGINE_ENGINECONFIGLOADER_H_
#define ENGINE_ENGINECONFIGLOADER_H_

//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "engine/config/EngineConfig.h"


//Forward declaration

class EngineConfigLoader {
public:
	EngineConfigLoader() = delete;
	virtual ~EngineConfigLoader() = default;

	static EngineConfig loadConfig();

	static void populateMonitorConfig(MonitorWindowCfg& cfg);

	static void populateDrawMgrConfig(DrawMgrCfg& cfg);

	static std::string getFilePath(const std::string& relativePath);

	static void populateImageContainerConfig(ImageContainerCfg& cfg);

	static void populateTextContainerConfig(TextContainerCfg& cfg);

	static void populateRsrcMgrConfig(RsrcMgrCfg& cfg);

	static void populateGameConfig(GameCfg& cfg);

	static void populateManagerHandlerCfg(ManagerHandlerCfg& cfg);
};

#endif /* ENGINE_ENGINECONFIGLOADER_H_ */
