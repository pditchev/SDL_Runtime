// Corresponding Header
#include "manager_utils/debug/DebugConsole.h"

// C system includes

// C++ system includes

// Third party includes
#include "utils/drawing/Color.h"

// Own includes
#include "sdl_utils/InputEvent.h"

int32_t DebugConsole::init(int64_t maxFrames, int32_t fontId){
	_maxFrames = maxFrames;

	Point textPos = Point(900, 80);
	_debugTexts[FPS_TEXT_IDX].create("0", fontId, Colors::BLUE, textPos);

	textPos._y += 40;
	_debugTexts[ACTIVE_TIMER_IDX].create("0", fontId, Colors::BLUE, textPos);


	return EXIT_SUCCESS;
}

void DebugConsole::handleEvent([[maybe_unused]]const InputEvent& e){
	if(e.type != TouchEvent::KEYBOARD_PRESS){
		return;
	}

	if(e.key == Keyboard::KEY_TILDA){
		_isActive = !_isActive;
	}
}

void DebugConsole::update([[maybe_unused]]int64_t elapsedMicroseconds, size_t activeTimers){
	constexpr auto microSecondsInASecond = 1000000;

	auto currFps = microSecondsInASecond / elapsedMicroseconds;
	if(currFps > _maxFrames){
		currFps = _maxFrames;
	}

	std::string textContent = "FPS: ";
	textContent.append(std::to_string(currFps));
	_debugTexts[FPS_TEXT_IDX].setText(textContent);

	textContent = "Active Timers: ";
	textContent.append(std::to_string(activeTimers));
	_debugTexts[ACTIVE_TIMER_IDX].setText(textContent);
}

void DebugConsole::draw() const {
	for(int32_t i = 0; i < DEBUG_TEXTS_COUNT; ++i){
		_debugTexts[i].draw();
	}
}

bool DebugConsole::isActive() const{
	return _isActive;
}

