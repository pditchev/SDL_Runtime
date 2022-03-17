// Corresponding Header
#include "utils/drawing/Rectangle.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes

const Rectangle Rectangle::ZERO(0, 0, 0, 0);
const Rectangle Rectangle::UNDEFINED(10000, 10000,10000, 10000);

Rectangle::Rectangle(int32_t x, int32_t y,int32_t w,int32_t h)
		: _x(x), _y(y), _w(w), _h(h) {}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

bool Rectangle::operator==(const Rectangle& other) const{
	return _x == other._x && _y == other._y && _w == other._w && _h == other._h;
}

bool Rectangle::operator!=(const Rectangle& other) const {
	return !operator==(other);
}

bool Rectangle::isPointInside(const Point& point) const {
	const bool isInsideX = ((point._x >= _x) && (point._x < _x + _w));
	const bool isInsideY = ((point._y >= _y) && (point._y < _y + _h));

	return isInsideX && isInsideY;
}

