// Corresponding Header
#include "manager_utils/managers/TimerMgr.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes
#include "manager_utils/time/TimerClient.h"

TimerMgr* gTimerMgr = nullptr;

int32_t TimerMgr::init(){
	_elapsedTime.getElapsed();

	return EXIT_SUCCESS;
}


void TimerMgr::deinit() {

}

void TimerMgr::process() {
	const int64_t msElapsed = _elapsedTime.getElapsed().toMilliseconds();
	for(auto& [timerId, timerData] : _timerMap){
		timerData.remaining -= msElapsed;
		if(0 > timerData.remaining){
			onTimerTimeout(timerId, timerData);
		}
	}
	removeTimersInternal();
}

void TimerMgr::startTimer(int32_t timerId, const TimerData& data){
	if(isActiveTimerId(timerId)){
		std::cerr << "Error! Trying to start an already existing timer with Id: " << timerId << std::endl;
		return;
	}
	_timerMap.emplace(timerId, data);
}

void TimerMgr::stopTimer(int32_t timerId){
	if(!isActiveTimerId(timerId)){
		std::cerr << "Error! Trying to stop a non-active timer with Id: " << timerId << std::endl;
		return;
	}
	_removeTimerSet.insert(timerId);
}

//	void TimerMgr::detachTimerClient(int32_t timerId)



bool TimerMgr::isActiveTimerId(int32_t timerId) const{
	return (_removeTimerSet.end() == _removeTimerSet.find(timerId))
			&& (_timerMap.end() != _timerMap.find(timerId));
}

size_t TimerMgr::getActiveTimersCount() const {
	return _timerMap.size();
}


void TimerMgr::onInitEnd(){
	_elapsedTime.getElapsed();
}

void TimerMgr::removeTimersInternal() {
	for (const int32_t timerId : _removeTimerSet) {
		auto mapIt = _timerMap.find(timerId);
		if (mapIt != _timerMap.end()) {
			_timerMap.erase(mapIt);
		}
	}
	//clear the removeTimerSet
	_removeTimerSet.clear();
}

void TimerMgr::onTimerTimeout(int32_t timerId, TimerData& timer){
	if(TimerType::ONESHOT == timer.timerType){
		_removeTimerSet.insert(timerId);
	}
	timer.tcInstance->onTimeout(timerId);
	timer.remaining += timer.interval;
}










