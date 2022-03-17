// Corresponding Header
#include "game/logic/InputInverter.h"

// C system includes

// C++ system includes
#include <iostream>

// Third party includes

// Own includes
#include "sdl_utils/InputEvent.h"

int32_t InputInverter::init(int32_t boardWidth, int32_t boardHeight){
	_boardWidth = boardWidth;
	_boardHeight = boardHeight;

	return EXIT_SUCCESS;
}

void InputInverter::setBoardFlipType(WidgetFlip flipType){
	_flipType = flipType;
}

void InputInverter::invertEvent(InputEvent &e){
	switch(_flipType){
	case WidgetFlip::NONE:
		break;
	case WidgetFlip::HORIZONTAL:
		e.pos._y = _boardHeight - e.pos._y;
		break;
	case WidgetFlip::VERTICAL:
		e.pos._x = _boardWidth - e.pos._x;
		break;
	case WidgetFlip::HORIZONTAL_AND_VERTICAL:
		e.pos._y = _boardHeight - e.pos._y;
		e.pos._x = _boardWidth - e.pos._x;
		break;
	default:
		break;
	}
}
