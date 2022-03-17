// Corresponding Header
#include "manager_utils/input/ButtonBase.h"

// C system includes

// C++ system includes


// Third party includes

// Own includes
#include "sdl_utils/InputEvent.h"

void ButtonBase::draw() const{
	Image::draw();
}

void ButtonBase::lockInput(){
	_isInputUnlocked = false;
	Image::setFrame(DISABLED);
}

void ButtonBase::unlockInput(){
	_isInputUnlocked = true;
	Image::setFrame(UNCLICKED);

}

bool ButtonBase::isInputUnlocked() const{
	return _isInputUnlocked;
}

bool ButtonBase::containsEvent(const InputEvent& e) const {
	return Image::containsPoint(e.pos);
}

void ButtonBase::destroy(){
	_isInputUnlocked = true;
	Image::destroy();
}













