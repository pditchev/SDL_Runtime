// Corresponding Header
#include "game/panels/ManagementConsole.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes


int32_t ManagementConsole::init(int32_t fontId, int32_t timerCapTimerId){
	_fontId = fontId;

	Point textPos = Point(1000, 0);
	remainingTime.create(std::to_string(gameTime).c_str(), fontId, Colors::BLUE, textPos);

	std::string str = "Check to the";
	textPos = Point(920, 500);
	announcement1.create(str.c_str(), fontId, Colors::RED, textPos);
	announcement1.hide();

	str = " ";
	textPos = Point(920, 600);
	announcement2.create(str.c_str(), fontId, Colors::RED, textPos);
	announcement2.hide();

	_timerCapTimerId = timerCapTimerId;

	startTimer(1000, _timerCapTimerId, TimerType::PULSE);

	return EXIT_SUCCESS;
}


void ManagementConsole::onTimeout(int32_t timerId) {
	if(_timerCapTimerId == timerId){

		const auto& remSeconds = std::stoi(remainingTime.getTextContent());
		remainingTime.setText(std::to_string(remSeconds - 1));

		if(0 == remSeconds){
			clearMoveTiles();
			finish();
		}

	} else{
		std::cerr << "Received unsupported timerId: " << timerId << std::endl;
	}
}

void ManagementConsole::draw() const {
	remainingTime.draw();
	announcement1.draw();
	announcement2.draw();
}


void ManagementConsole::startTimerCap(){
	remainingTime.setText(std::to_string(gameTime));
}

void ManagementConsole::onCheck(const Defines::PlayerId &player) {
	if(player == Defines::WHITE_PLAYER_ID){
		announcement2.setText("Black Player");
	}
	else {
		announcement2.setText("White Player");
	}

	announcement1.show();
	announcement2.show();
}

void ManagementConsole::onCheckMate(const Defines::PlayerId &winner){
	announcement1.setText("CheckMate to the");

	if(winner == Defines::WHITE_PLAYER_ID){
		announcement2.setText("Black Player");
	}
	else {
		announcement2.setText("White Player");
	}

	announcement1.show();
	announcement2.show();
}

void ManagementConsole::onRemoveCheck(){
	announcement1.hide();
	announcement2.hide();
}


