#ifndef INCLUDE_GAME_PIECES_TYPES_BISHOP_H_
#define INCLUDE_GAME_PIECES_TYPES_BISHOP_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"

//Forward declaration

class Bishop : public ChessPiece {
public:

private:
	std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const final;

	static constexpr int8_t allowedDirs = 4;
	static constexpr int8_t maxRootMoves = 7;
	static constexpr std::array<Defines::Direction, allowedDirs> bishopDirs { Defines::UP_LEFT,
																	   Defines::UP_RIGHT,
																	   Defines::DOWN_RIGHT,
																	   Defines::DOWN_LEFT };
};

#endif /* INCLUDE_GAME_PIECES_TYPES_BISHOP_H_ */
