#ifndef INCLUDE_GAME_PIECES_TYPES_KNIGHT_H_
#define INCLUDE_GAME_PIECES_TYPES_KNIGHT_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"

//Forward declaration

class Knight : public ChessPiece {
public:

private:
	std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const final;

	static constexpr int8_t allowedDirs = 8;
	static constexpr int8_t maxRootMoves = 1;	// how many fields can access in one!! direction at most !!!
	static constexpr std::array<Defines::KnightDirections, allowedDirs> knightDirs { Defines::KNIGHT_UP_LEFT,
																			  Defines::KNIGHT_UP_RIGHT,
																			  Defines::KNIGHT_RIGHT_UP,
																			  Defines::KNIGHT_RIGHT_DOWN,
																			  Defines::KNIGHT_DOWN_RIGHT,
																			  Defines::KNIGHT_DOWN_LEFT,
																			  Defines::KNIGHT_LEFT_DOWN,
																			  Defines::KNIGHT_LEFT_UP };
};

#endif /* INCLUDE_GAME_PIECES_TYPES_KNIGHT_H_ */
