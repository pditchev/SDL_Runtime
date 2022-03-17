#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_

//C system headers

//C++ system headers
#include <cstdint>
#include <iostream>

//Other libraries headers

//Own components headers
#include "utils/drawing/DrawParams.h"

//Forward declaration


class Widget {
public:
	//my
	virtual ~Widget() = default;

	void draw() const;

	void reset();

	void setFlipType(WidgetFlip flipType);

	void setWidth(int32_t width);
	void setHeight(int32_t height);

	int32_t getWidth() const;
	int32_t getHeight() const;

	int32_t getX() const;
	int32_t getY() const;

	void setPosition(const Point& pos);
	void setPosition(int32_t x, int32_t y);

	void setOpacity(int32_t opacity);

	Point getPosition() const;
	int32_t getOpacity() const;

	void setRotation(double angle);
	double getRotation() const;
	void rotateRight(double delta);
	void rotateLeft(double delta);

	void setRotationCenter(const Point& rotCenter);

	void activateAlphaModulation();
	void deactivateAlphaModulation();

	void show();
	void hide();
	void changeVisibility();

	void moveRight(int32_t delta);
	void moveLeft(int32_t delta);
	void moveUp(int32_t delta);
	void moveDown(int32_t delta);

	bool containsPoint(const Point& pos) const;

	bool isVisible() const;

	bool isCreated() const;

protected:

  DrawParams _drawParams;

  bool _isCreated = false;
  bool _isDestroyed = true;
  bool _isVisible = true;
  bool _isAlphaModulationEnabled = false;
};

#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_DRAWING_WIDGET_H_ */
