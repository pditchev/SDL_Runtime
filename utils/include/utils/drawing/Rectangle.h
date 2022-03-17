#ifndef UTILS_DRAWING_RECTANGLE_H_
#define UTILS_DRAWING_RECTANGLE_H_

// C system includes

// C++ system includes
#include <cstdint>

// Third party includes

// Own includes
#include "utils/drawing/Point.h"
//#include "drawing/Point.h"

// Forward Declarations

struct Rectangle {
	Rectangle() = default;
	Rectangle(int32_t x, int32_t y, int32_t w, int32_t h);
	~Rectangle();

	int32_t _x = 0;
	int32_t _y = 0;
	int32_t _w = 0;
	int32_t _h = 0;

	bool operator==(const Rectangle& other) const;
	bool operator!=(const Rectangle& other) const;

	bool isPointInside(const Point& point) const;

	static const Rectangle ZERO;
	static const Rectangle UNDEFINED;
};

#endif /* UTILS_DRAWING_RECTANGLE_H_ */
