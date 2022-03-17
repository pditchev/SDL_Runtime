#ifndef INCLUDE_GAME_PIECES_TYPES_ROOK_H_
#define INCLUDE_GAME_PIECES_TYPES_ROOK_H_
//C system headers

//C++ system headers

//Other libraries headers

//Own components headers
#include "game/pieces/types/ChessPiece.h"

//Forward declaration

class Rook : public ChessPiece {
public:
	// void setBoardPos(const BoardPos& boardPos) final;

private:
	std::unordered_map<Defines::Direction, MoveDirection> getBoardMoves() const final;

	static constexpr int8_t allowedDirs = 4;
	static constexpr int8_t maxRootMoves = 7;
	static constexpr std::array<Defines::Direction, allowedDirs> rookDirs{ Defines::UP,
																		   Defines::RIGHT,
																		   Defines::DOWN,
																		   Defines::LEFT };
};


#endif /* INCLUDE_GAME_PIECES_TYPES_ROOK_H_ */
