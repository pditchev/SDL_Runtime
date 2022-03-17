#ifndef INCLUDE_GAME_UTILS_BOARDPOS_H_
#define INCLUDE_GAME_UTILS_BOARDPOS_H_
//C system headers

//C++ system headers

//Other libraries headers
#include <cstdlib>

//Own components headers

//Forward declaration

struct BoardPos{
	BoardPos() = default;
	BoardPos(int32_t inputRow, int32_t inputCol) : row(inputRow), col(inputCol) {}

	int32_t row {};
	int32_t col {};

	bool operator==(const struct BoardPos& other) const {
		return row == other.row && col==other.col;
	}

	bool operator!=(const struct BoardPos& other) const{
		return !operator==(other);
	}

};

#endif /* INCLUDE_GAME_UTILS_BOARDPOS_H_ */
