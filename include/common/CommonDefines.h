#ifndef COMMON_COMMONDEFINES_H_
#define COMMON_COMMONDEFINES_H_
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declaration

namespace TextureId{

enum ResourceId{
	CHESS_BOARD,
	TARGET,
	WHITE_PIECES,
	BLACK_PIECES,
	MOVE_TILES,
	PROMOTION_BUTTON
};

} //namespace TextureId

namespace FontId{
enum FontIdKeys{
		ANGELINE_VINTAGE_40,
		ANGELINE_VINTAGE_80
};
} //namespace FontId

namespace TimerId{
enum Key{
	BLINK_TARGET_TIMER_ID,
	TIMER_CAP_TIMER_ID
};
}


#endif /* COMMON_COMMONDEFINES_H_ */
