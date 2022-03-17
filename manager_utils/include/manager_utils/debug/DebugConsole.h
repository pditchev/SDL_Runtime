#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DEBUG_DEBUGCONSOLE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DEBUG_DEBUGCONSOLE_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Text.h"

//Forward declaration
struct InputEvent;

enum DebugTextsIdx{
	FPS_TEXT_IDX,
	ACTIVE_TIMER_IDX,

	DEBUG_TEXTS_COUNT
};


class DebugConsole {
public:
	int32_t init(int64_t maxFrames, int32_t fontId);
	void handleEvent([[maybe_unused]]const InputEvent& e);
	void update(int64_t elapsedMicroseconds, size_t activeTimers);
	void draw() const;
	bool isActive() const;
private:
	Text _debugTexts[DEBUG_TEXTS_COUNT];
	int64_t _maxFrames = 0; //used to determine the current FPS
	int32_t _updateCounter = 0; //used for skipping turns
	bool _isActive = false;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DEBUG_DEBUGCONSOLE_H_ */






