#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers
#include "game/Game.h"
#include "sdl_utils/InputEvent.h"
#include "manager_utils/managers/ManagerHandler.h"
#include "manager_utils/debug/DebugConsole.h"

//Forward declaration
struct EngineConfig;

class Engine {
public:
	int32_t init(const EngineConfig& cfg);
	void deinit();
	void start();
	void draw();
private:
	void mainLoop();
	void drawFrame();
	bool processFrame();
	void handleEvent();
	void limitFPS(int64_t elapsedTimeMicroseconds);

	ManagerHandler _managerHandler;
	InputEvent _event;
	Game _game;
	DebugConsole _debugConsole;
};

#endif /* ENGINE_ENGINE_H_ */
