#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "manager_utils/drawing/Image.h"
//Forward declaration
struct InputEvent;


enum ButtonStates {
	UNCLICKED, CLICKED, DISABLED
};

class ButtonBase : public Image {
public:
	virtual ~ButtonBase() = default;

	virtual void handleEvent(const InputEvent& e) = 0;
	virtual void draw() const;
	void lockInput();
	void unlockInput();
	bool isInputUnlocked() const;
	bool containsEvent(const InputEvent& e) const ;
	void destroy();

private:
//	Rectangle _boundRect = Rectangle::ZERO;
	bool _isInputUnlocked = true;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_INPUT_BUTTONBASE_H_ */
