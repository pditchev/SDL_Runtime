#ifndef UTILS_DRAWING_DRAWPARAMS_H_
#define UTILS_DRAWING_DRAWPARAMS_H_

// C system includes

// C++ system includes
#include <cstdint>

// Third party includes

// Own includes
#include "utils/drawing/Point.h"
#include "utils/drawing/Rectangle.h"

// Forward Declarations

inline constexpr auto INVALID_RSRC_ID = -1;
inline constexpr int32_t FULL_OPACITY = 255;
inline constexpr int32_t ZERO_OPACITY = 0;
inline constexpr auto FULL_ROTATION = 360.0;


enum class BlendMode : uint8_t {
	NONE = 0, //value for SDL_BLENDMODE_NONE
	BLEND = 1, //value for SDL_BLENDMODE_BLEND
	ADD = 2, //value for SDL_BLENDMODE_ADD
	MOD = 4 //value for SDL_BLENDMODE_MODE
};

enum class WidgetType : uint8_t {
	IMAGE,
	TEXT,
	UNKNOWN
};

enum class WidgetFlip : uint8_t {
    NONE,
    HORIZONTAL,
    VERTICAL,
    HORIZONTAL_AND_VERTICAL
};

struct DrawParams{
	void reset();

	Rectangle frameRect = Rectangle::ZERO;

	Point pos = Point::UNDEFINED;

	double rotationAngle = 0.0;
	Point rotationCenter = Point::ZERO;

	int32_t width = 0;
	int32_t height = 0;

	int32_t opacity = FULL_OPACITY;

	union{
		int32_t rsrcId = INVALID_RSRC_ID;
		int32_t textId;
	};

	WidgetType widgetType = WidgetType::UNKNOWN;

	WidgetFlip flipType = WidgetFlip::NONE;
};


#endif /* UTILS_DRAWING_DRAWPARAMS_H_ */
