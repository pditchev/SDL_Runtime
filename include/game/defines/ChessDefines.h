#ifndef INCLUDE_DEFINES_CHESSDEFINES_H_
#define INCLUDE_DEFINES_CHESSDEFINES_H_
//C system headers

//C++ system headers
#include <cstdint>

//Other libraries headers

//Own components headers

//Forward declaration
namespace Defines{
enum PlayerId {
	WHITE_PLAYER_ID,
	BLACK_PLAYER_ID,
	PLAYERS_COUNT
};

enum Direction {
	UP_LEFT,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	DIRECTION_COUNT
};

enum KnightDirections {
	KNIGHT_UP_LEFT,
	KNIGHT_UP_RIGHT,
	KNIGHT_RIGHT_UP,
	KNIGHT_RIGHT_DOWN,
	KNIGHT_DOWN_RIGHT,
	KNIGHT_DOWN_LEFT,
	KNIGHT_LEFT_DOWN,
	KNIGHT_LEFT_UP,
	KNIGHT_DIRECTION_COUNT
};

enum PawnDefines{
	WHITE_PLAYER_START_PAWN_ROW = 6,
	BLACK_PLAYER_START_PAWN_ROW = 1,
	WHITE_PLAYER_START_END_ROW = 0,
	BLACK_PLAYER_START_END_ROW = 7,

	PAWNS_COUNT = 8
};

enum RowDefines{
	WHITE_PLAYER_START_ROW = 7,
	BLACK_PLAYER_START_ROW = 0
};

enum RookDefines{ // defines row of the Rook
	QUEEN_SIDE_ROOK = 0,
	KING_SIDE_ROOK = 7
};
}

enum class PieceType : uint8_t {
	KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, UNKNOWN
};

enum class TileType : uint8_t {
	MOVE, GUARD, TAKE
};



#endif /* INCLUDE_DEFINES_CHESSDEFINES_H_ */
