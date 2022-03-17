#ifndef INCLUDE_GAME_PIECES_TYPES_QUEEN_H_
#define INCLUDE_GAME_PIECES_TYPES_QUEEN_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"

//Forward declaration

class Queen : public ChessPiece {
public:

private:
	std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const final;

	static constexpr int8_t allowedDirs = 8;
	static constexpr int8_t maxRootMoves = 7;	// how many fields can access in one!! direction at most !!!
	static constexpr std::array<Defines::Direction, allowedDirs> queenDirs { Defines::UP,
																			  Defines::UP_RIGHT,
																			  Defines::RIGHT,
																			  Defines::DOWN_RIGHT,
																			  Defines::DOWN,
																			  Defines::DOWN_LEFT,
																			  Defines::LEFT,
																			  Defines::UP_LEFT };

};

#endif /* INCLUDE_GAME_PIECES_TYPES_QUEEN_H_ */
