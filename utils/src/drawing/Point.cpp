// Corresponding Header
#include "utils/drawing/Point.h"

// C system includes

// C++ system includes

// Third party includes

// Own includes

const Point Point::ZERO(0, 0);
const Point Point::UNDEFINED(10000, 10000);

Point::Point(int32_t x, int32_t y) : _x(x), _y(y){}

bool Point::operator==(const Point& other) const {
	return _x == other._x && _y == other._y;
}

bool Point::operator!=(const Point& other) const{
	return !operator==(other);
}
