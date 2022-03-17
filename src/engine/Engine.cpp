// Corresponding Header
#include "engine/Engine.h"

// C system includes

// C++ system includes
#include <iostream>
#include <string>

// Third party includes

// Own includes
#include "sdl_utils/Texture.h"
#include "utils/thread/ThreadUtils.h"
#include "utils/time/Time.h"

#include "engine/config/EngineConfig.h"
#include "manager_utils/managers/DrawMgr.h"
#include "manager_utils/managers/TimerMgr.h"
//#include "manager_utils/managers/RsrcMgr.h"

int32_t Engine::init(const EngineConfig& cfg){
	if(EXIT_SUCCESS != _managerHandler.init(cfg.managerHandlerCfg)){
		std::cerr << "ManagerHandler.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _event.init()){
		std::cerr << "InputEvent.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _game.init(cfg.gameCfg)){
		std::cerr << "game.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	if(EXIT_SUCCESS != _debugConsole.init(cfg.managerHandlerCfg.drawMgrCfg.maxFrameRate,
										  cfg.debugConsoleFontId)){
		std::cerr << "_debugConsole.init() failed!" << std::endl;
		return EXIT_FAILURE;
	}

	gTimerMgr->onInitEnd();

	return EXIT_SUCCESS;
}

void Engine::draw(){
//	return EXIT_SUCCESS;
}

void Engine::deinit(){
	_game.deinit();
	_event.deinit();
	_managerHandler.deinit();
}

void Engine::start(){
	mainLoop();
}

void Engine::mainLoop(){
	Time time;

	while(true){
		const bool shouldExit = processFrame();
		if(shouldExit){
			break;
		}

		const auto elapsedTime = time.getElapsed().toMicroseconds();
		if(_debugConsole.isActive()){
			_debugConsole.update(elapsedTime, gTimerMgr->getActiveTimersCount());
		}

		limitFPS(elapsedTime);
	}
}

void Engine::drawFrame(){

	gDrawMgr->clearScreen();

	_game.draw();
	if(_debugConsole.isActive()){
	   _debugConsole.draw();
	}

	gDrawMgr->finishFrame();
}

bool Engine::processFrame(){
	_managerHandler.process();

	while(_event.pollEvent()){
		if(_event.checkForExitRequest()){
			return true;
		}

		handleEvent();
	}

	drawFrame();

	return false;
}

void Engine::handleEvent(){
	_game.handleEvent(_event);
	_debugConsole.handleEvent(_event);
}

void Engine::limitFPS(int64_t elapsedTimeMicroSeconds){
	//constexpr auto maxFrames = 30;
	constexpr auto microSecondsInASecond = 1000000;
	const auto microSecondsInAFrame = microSecondsInASecond / gDrawMgr->getMaxFrameRate();
	const int64_t sleepDurationMicroSeconds = microSecondsInAFrame - elapsedTimeMicroSeconds;

	if(sleepDurationMicroSeconds > 0){
		Threading::sleepFor(sleepDurationMicroSeconds);
	}
}


